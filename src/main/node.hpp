/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI - Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#ifndef ELVEX_NODE_H
#define ELVEX_NODE_H

#include <vector>
#include <forward_list>

#ifdef OUTPUT_XML
#include <libxml/tree.h>
#endif

#include "facade.hpp"
#include "shared_ptr.hpp"
#include "orderspecs.hpp"

class Generator;

/**
 * One derivation alternative in a packed Forest.
 * Its child forests may be linearized in RHS order, all permutations, or an
 * order satisfying explicit precedence constraints.
 */
class Node : public Facade,
             public std::enable_shared_from_this<class Node>
{

public:
    typedef std::vector<forestPtr> vectorForests;

private:
    vectorForests forests;
    std::vector<uint32_t> rhsIndexes;
    OrderSpecs orderSpecs;
    std::forward_list<std::string> output;
    bool withSpaces;
    bool unordered;

    /** Generate child forests only once, before combining their outputs. */
    void generateChildForests(Generator *generator, bool randomResult, bool singleResult);

    /** Enumerate outputs according to RHS order, permutations or constraints. */
    void linearizeChildren();

public:
    Node(bool withSpaces, bool unordered);

    ~Node(void);

    static nodePtr create(bool withSpaces, bool unordered);

    bool empty() const;

    vectorForests::iterator begin();

    vectorForests::iterator end();

    vectorForests::const_iterator cbegin() const;

    vectorForests::const_iterator cend() const;

    size_t size() const;

    forestPtr at(size_t);

    void push_back(const forestPtr &);
    void push_back(uint32_t rhsIndex, const forestPtr &);

    const std::forward_list<std::string>::const_iterator output_cbegin(void) const;

    const std::forward_list<std::string>::const_iterator output_cend(void) const;

    bool getWithSpace() const;

    uint32_t rhsIndexAt(size_t) const;

    void setOrderSpecs(const OrderSpecs &);
    
    const OrderSpecs &getOrderSpecs() const;

    const std::vector<uint32_t> &getRhsIndexes() const;

#ifdef OUTPUT_XML
    void toXML(xmlNodePtr, xmlNodePtr) const;
#endif

    /**
     * Compute the Cartesian product of child-forest outputs in the supplied
     * order, respecting the node's spacing mode.
     */
    void generateLR(std::string &currentCombination, const vectorForests &forestsToGenerate);

    /**
     * Enumerate child orders for an explicitly unordered rule.
     * This can grow factorially with the number of children.
     */
    void generatePermutations(vectorForests &forestsToGenerate, int start, int end);

    void generateWithOrder(const std::vector<size_t> &order);

    /**
     * Return valid child orders satisfying the precedence graph.
     * An empty set indicates that no valid ordering was found.
     */
    std::vector<std::vector<size_t>> computeTopologicalOrders() const;

    /**
     * Generate child forests, then linearize the selected derivation orders.
     * Rejects contradictory unordered/ordered configurations.
     */
    void generate(class Generator *generator, bool randomResult, bool singleResult);
};

#endif // ELVEX_NODE_H
