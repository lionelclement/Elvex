#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
TEST_DIR="${SCRIPT_DIR}/regression"

ELVEX_BIN="${1:-${ELVEX_BIN:-${ROOT_DIR}/bin/elvex}}"
ELVEXLEXICON_BIN="${2:-${ELVEXLEXICON_BIN:-${ROOT_DIR}/bin/elvexlexicon}}"

if [[ ! -x "${ELVEX_BIN}" ]]; then
  echo "ERROR: elvex binary not found or not executable: ${ELVEX_BIN}" >&2
  echo "Usage: $0 [path/to/elvex] [path/to/elvexlexicon]" >&2
  exit 2
fi

if [[ ! -d "${TEST_DIR}" ]]; then
  echo "ERROR: regression test directory not found: ${TEST_DIR}" >&2
  exit 2
fi

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "${TMP_DIR}"' EXIT

normalize_output() {
  # Compare outputs as a set of generated lines:
  #   - normalize CRLF to LF
  #   - keep empty lines
  #   - canonicalize whitespace-only/control-only lines as true empty lines
  #   - sort complete lines as atomic strings
  #
  # Important: this does NOT sort words inside a line.
  # For example, "b a" remains the single line "b a".
  LC_ALL=C perl -pe '
    s/\r$//;
    s/[\x00-\x08\x0B\x0C\x0E-\x1F\x7F]//g;
    $_ = "\n" if /^[[:space:]]*$/;
  ' "$1" | LC_ALL=C sort
}

build_compacted_lexicon_if_needed() {
  local name="$1"
  local macros="$2"
  local pattern="$3"
  local morpho="$4"
  local compacted="$5"
  local build_stdout="${TMP_DIR}/${name}.build.stdout"
  local build_stderr="${TMP_DIR}/${name}.build.stderr"

  if [[ ! -f "${pattern}" && ! -f "${morpho}" ]]; then
    return 1
  fi

  if [[ ! -x "${ELVEXLEXICON_BIN}" ]]; then
    echo "[FAIL] ${name}: elvexlexicon binary not found or not executable: ${ELVEXLEXICON_BIN}" >&2
    echo "Usage: $0 [path/to/elvex] [path/to/elvexlexicon]" >&2
    return 2
  fi

  for file in "${macros}" "${pattern}" "${morpho}"; do
    if [[ ! -f "${file}" ]]; then
      echo "[FAIL] ${name}: missing file ${file}" >&2
      return 2
    fi
  done

  echo "[BUILD] ${name}"

  if ! "${ELVEXLEXICON_BIN}" \
      --macros-file "${macros}" \
      --pattern-file "${pattern}" \
      --morpho-file "${morpho}" \
      --compacted-lexicon-file "${compacted}" \
      build > "${build_stdout}" 2> "${build_stderr}"; then
    echo "[FAIL] ${name}: elvexlexicon returned an error" >&2
    if [[ -s "${build_stderr}" ]]; then
      echo "build stderr was:" >&2
      cat "${build_stderr}" >&2
    fi
    if [[ -s "${build_stdout}" ]]; then
      echo "build stdout was:" >&2
      cat "${build_stdout}" >&2
    fi
    return 2
  fi

  return 0
}

run_one() {
  local name="$1"
  local rules="${TEST_DIR}/${name}.rules"
  local lexicon="${TEST_DIR}/${name}.lexicon"
  local input="${TEST_DIR}/${name}.input"
  local stdin_file="${TEST_DIR}/${name}.stdin"
  local expected="${TEST_DIR}/${name}.expected"
  local expected_stderr="${TEST_DIR}/${name}.stderr"
  local macros="${TEST_DIR}/${name}.macros"
  local pattern="${TEST_DIR}/${name}.pattern"
  local morpho="${TEST_DIR}/${name}.morpho"
  local compacted="${TMP_DIR}/${name}.compacted"
  local actual="${TMP_DIR}/${name}.actual"
  local stderr_log="${TMP_DIR}/${name}.stderr"
  local actual_sorted="${TMP_DIR}/${name}.actual.sorted"
  local expected_sorted="${TMP_DIR}/${name}.expected.sorted"
  local stderr_sorted="${TMP_DIR}/${name}.stderr.sorted"
  local expected_stderr_sorted="${TMP_DIR}/${name}.expected.stderr.sorted"
  local compacted_status=1
  local input_mode=""
  local input_source=""

  echo "[TEST] ${name}"

  if [[ -f "${stdin_file}" ]]; then
    input_mode="stdin"
    input_source="${stdin_file}"
  elif [[ -f "${input}" ]]; then
    input_mode="input"
    input_source="${input}"
  else
    echo "[FAIL] ${name}: missing input file ${input} or ${stdin_file}" >&2
    return 1
  fi

  for file in "${rules}" "${lexicon}" "${expected}" "${input_source}"; do
    if [[ ! -f "${file}" ]]; then
      echo "[FAIL] ${name}: missing file ${file}" >&2
      return 1
    fi
  done

  if build_compacted_lexicon_if_needed "${name}" "${macros}" "${pattern}" "${morpho}" "${compacted}"; then
    compacted_status=0
  else
    compacted_status=$?
  fi
  if [[ "${compacted_status}" -eq 2 ]]; then
    return 1
  fi

  local elvex_args=(
    --rules-file "${rules}"
    --lexicon-file "${lexicon}"
  )

  if [[ -f "${macros}" ]]; then
    elvex_args+=(--macros-file "${macros}")
  fi

  if [[ "${compacted_status}" -eq 0 ]]; then
    elvex_args+=(--compacted-lexicon-file "${compacted}")
  fi

  if [[ "${input_mode}" == "stdin" ]]; then
    elvex_args+=(--server-stdio)
    if ! "${ELVEX_BIN}" "${elvex_args[@]}" < "${input_source}" > "${actual}" 2> "${stderr_log}"; then
      echo "[FAIL] ${name}: elvex returned an error" >&2
      if [[ -s "${stderr_log}" ]]; then
        echo "stderr was:" >&2
        cat "${stderr_log}" >&2
      fi
      if [[ -s "${actual}" ]]; then
        echo "stdout was:" >&2
        cat "${actual}" >&2
      fi
      return 1
    fi
  else
    elvex_args+=(--input-file "${input_source}")
    if ! "${ELVEX_BIN}" "${elvex_args[@]}" > "${actual}" 2> "${stderr_log}"; then
      echo "[FAIL] ${name}: elvex returned an error" >&2
      if [[ -s "${stderr_log}" ]]; then
        echo "stderr was:" >&2
        cat "${stderr_log}" >&2
      fi
      if [[ -s "${actual}" ]]; then
        echo "stdout was:" >&2
        cat "${actual}" >&2
      fi
      return 1
    fi
  fi

  normalize_output "${actual}" > "${actual_sorted}"
  normalize_output "${expected}" > "${expected_sorted}"

  if ! diff -u "${expected_sorted}" "${actual_sorted}"; then
    echo "[FAIL] ${name}" >&2
    if [[ -s "${stderr_log}" ]]; then
      echo "stderr was:" >&2
      cat "${stderr_log}" >&2
    fi
    echo "Actual stdout was:" >&2
    cat "${actual}" >&2
    return 1
  fi

  if [[ -f "${expected_stderr}" ]]; then
    normalize_output "${stderr_log}" > "${stderr_sorted}"
    normalize_output "${expected_stderr}" > "${expected_stderr_sorted}"

    if ! diff -u "${expected_stderr_sorted}" "${stderr_sorted}"; then
      echo "[FAIL] ${name}: stderr mismatch" >&2
      echo "Actual stderr was:" >&2
      cat "${stderr_log}" >&2
      return 1
    fi
  elif [[ -s "${stderr_log}" ]]; then
    echo "[WARN] ${name}: stderr was not empty" >&2
    cat "${stderr_log}" >&2
  fi

  echo "[ OK ] ${name}"
}

main() {
  local failed=0
  local test_file name
  shopt -s nullglob
  local tests=("${TEST_DIR}"/*.rules)
  shopt -u nullglob

  if [[ "${#tests[@]}" -eq 0 ]]; then
    echo "ERROR: no regression tests found in ${TEST_DIR}" >&2
    exit 2
  fi

  for test_file in "${tests[@]}"; do
    name="$(basename "${test_file}" .rules)"
    run_one "${name}" || failed=1
  done

  if [[ "${failed}" -ne 0 ]]; then
    echo "Regression tests failed." >&2
    exit 1
  fi

  echo "All regression tests passed."
}

main "$@"
