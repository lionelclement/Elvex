SUFFIXES: .poslemma .formmorpho .lemma2 .lemmamorpho .elvex .complete .lefff .pattern

CLEANFILES = lefff.fsa lefff.tbl
BUILDLEXICON = ../../src/elvexbuildlexicon

all:
	@make lefff.fsa

%.poslemma: %.pos %.lemma
	@echo "build $@"
	@paste $^ | tr '\t' '#' > $@

%.formmorpho: %.form %.predmorpho
	@echo "build $@"
	@paste $^ | tr '\t' '#' > $@

%.pred: %.lemma
	@echo "build $@"
	@sed -e 's/^\(.*\)/PRED:\1,/' < $^ > $@

%.predmorpho: %.pred %.morpho
	@echo "build $@"
	@paste $*.pred $*.morpho | sed -e 's/	//' -e 's/\(.*\)/[\1]/' -e 's/,]/]/' > $@

%.elvex: %.poslemma %.formmorpho
	@echo "build $@"
	@paste $^ | sort -u > $@

%.fsa: %.elvex
	@echo "build $@"
	@$(BUILDLEXICON) -d . -f $* build $<

%.form: %.complete
	@echo "build $@"
	@grep -v '^//' < $< | cut -f1 > $@

%.pos: %.complete
	@echo "build $@"
	@grep -v '^//' < $< | cut -f2 > $@

%.lemma: %.complete
	@echo "build $@"
	@grep -v '^//' < $< | cut -f3 > $@

%.morpho: %.complete
	@echo "build $@"
	@grep -v '^//' < $< | cut -f4 > $@

%.complete: %.lefff %.pattern
	@echo "build $@"
	@perl completeLefff.pl $*.lefff $*.pattern > $@
