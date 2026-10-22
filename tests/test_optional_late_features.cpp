// Non-regression test for PASS/UNFOLD normalization propagation.
// Build against the actual Elvex source tree (not a mock).
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "item.hpp"
#include "rule.hpp"
#include "terms.hpp"
#include "features.hpp"
#include "feature.hpp"
#include "value.hpp"
#include "listfeatures.hpp"

static featuresPtr withHead(uint32_t code)
{
    return Features::create(Feature::createHead(Value::createIdentifier(code)));
}

static Item *optionalItem()
{
    std::vector<termsPtr> rhs{Terms::create(101, true)}; // one optional child
    rulePtr rule = Rule::create(1, "late-features.rules", false, false, 100, rhs);
    return Item::create(rule, 0, Item::POSTERM_NA);
}

static int failures = 0;

static void expect(const char *label, bool observed, bool expected)
{
    if (observed != expected)
    {
        ++failures;
        std::cerr << "[FAIL] " << label << ": observed " << observed
                  << ", expected " << expected << '\n';
    }
    else
    {
        std::cout << "[PASS] " << label << '\n';
    }
}

static void checkLateChange(const char *label, const std::function<void(Item *)> &mutate)
{
    Item *item = optionalItem();
    item->markNormalizationPropagated(0);
    expect("unchanged witness is stable", item->needsNormalizationPropagation(0), false);

    mutate(item);
    // Required behavior: newly available traits must reach the PASS variants.
    expect(label, item->needsNormalizationPropagation(0), true);
    delete item;
}

int main()
{
    // Control: the patch correctly notices changes in reverse references.
    Item *item = optionalItem();
    item->markNormalizationPropagated(0);
    expect("initial witness stable", item->needsNormalizationPropagation(0), false);
    item->addRef(0x1234);
    expect("new ref causes propagation", item->needsNormalizationPropagation(0), true);
    item->markNormalizationPropagated(0);
    expect("same refs no longer cause propagation", item->needsNormalizationPropagation(0), false);
    item->clearNormalizedAt(0);
    expect("cleared witness can propagate", item->needsNormalizationPropagation(0), true);
    delete item;

    // Replacing a structure by a distinct object with identical content
    // must not trigger re-propagation.
    item = optionalItem();
    item->setInheritedFeatures(withHead(5001));
    item->markNormalizationPropagated(0);
    item->setInheritedFeatures(withHead(5001));
    expect("same feature content does not propagate", item->needsNormalizationPropagation(0), false);
    delete item;

    // Each scenario changes only a feature structure (not refs/order specs).
    checkLateChange("late inherited feature (up arrow)", [](Item *item) {
        item->setInheritedFeatures(withHead(1001));
    });
    checkLateChange("late inherited child feature (down arrow 1)", [](Item *item) {
        item->getInheritedChildFeatures()->add(0, withHead(1001));
    });
    checkLateChange("late synthesized feature (double up arrow)", [](Item *item) {
        item->setSynthesizedFeatures(withHead(1002));
    });
    checkLateChange("late synthesized child feature (double down arrow 1)", [](Item *item) {
        item->getSynthesizedChildFeatures()->add(0, withHead(1002));
    });

    // A deep mutation must be detected even if the old Features object's
    // serialized identity was cached before the mutation.
    checkLateChange("late in-place inherited feature value", [](Item *item) {
        featuresPtr features = withHead(2001);
        item->setInheritedFeatures(features);
        item->markNormalizationPropagated(0);
        (void)features->peekCoreSerialString(); // populate the parent cache
        features->front()->setValue(Value::createIdentifier(2002));
    });
    checkLateChange("late in-place inherited child value", [](Item *item) {
        featuresPtr features = withHead(3001);
        item->getInheritedChildFeatures()->add(0, features);
        item->markNormalizationPropagated(0);
        (void)features->peekCoreSerialString();
        features->front()->setValue(Value::createIdentifier(3002));
    });

    if (failures)
    {
        std::cerr << failures << " failure(s): the normalization witness misses late feature changes.\n";
        return 1;
    }
    std::cout << "All normalization propagation checks passed.\n";
    return 0;
}
