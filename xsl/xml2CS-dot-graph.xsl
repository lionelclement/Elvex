<?xml version="1.0" encoding="UTF-8"?>
<!-- **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** -->
 

<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="text" encoding="UTF-8"/>

    <xsl:param name="size">100%</xsl:param>
    <xsl:param name="margin">0</xsl:param>
    <xsl:param name="nodesep">0.75</xsl:param>
    <xsl:param name="ranksep">0</xsl:param>

    <!--################################################## # ################################################## -->
    <xsl:template match="/ROOT">
        <xsl:text>digraph G{&#10;graph[center=&quot;yes&quot;,size=&quot;</xsl:text>
        <xsl:value-of select="$size"/>
        <xsl:text>&quot;</xsl:text>
        <xsl:text>];&#10;node[fontnames=&quot;Palatino-Roman&quot;,fontsize=&quot;12&quot;,fontcolor=&quot;black&quot;,style=&quot;filled&quot;,fillcolor=&quot;white&quot;,width=&quot;0&quot;,height=&quot;0&quot;,shape=&quot;ellipse&quot;,penwidth=&quot;1&quot;];&#10;edge[arrowtail=&quot;none&quot;,arrowhead=&quot;normal&quot;];&#10;</xsl:text>

        <xsl:apply-templates select="FOREST"/>

        <xsl:text>}&#10;</xsl:text>
    </xsl:template>

    <!--################################################## # Dessine le contenu
        de la forêt une seule fois ################################################## -->
    <xsl:template match="FOREST[NODE/SON]">
        <xsl:variable name="idF" select="@id" />
    <xsl:value-of select="$idF"/>
        <xsl:text>[shape=&quot;egg&quot;,style=&quot;filled&quot;,height=&quot;0.1&quot;,width=&quot;0.1&quot;,fontcolor=&quot;black&quot;</xsl:text>
        <xsl:text>,label=&quot;</xsl:text>
        <xsl:apply-templates select="OUTPUT"/>
        <xsl:text>&quot;];&#10;</xsl:text>

        <xsl:choose>
            <xsl:when test="count(NODE) > 0">
                <xsl:for-each select="NODE">
                    <xsl:variable name="idN" select="@id"/>
                    <xsl:value-of select="$idN"/>
                    <xsl:text>[shape=&quot;circle&quot;,height=&quot;0.15&quot;,width=&quot;0.15&quot;,fontcolor=&quot;black&quot;</xsl:text>
                    <xsl:text>,label=&quot;</xsl:text>
                    <xsl:apply-templates select="OUTPUT" />
                    <xsl:text>&quot;];&#10;</xsl:text>

                    <xsl:value-of select="$idF"/>
                    <xsl:text>-&gt;</xsl:text>
                    <xsl:value-of select="$idN"/>
                    <xsl:text>;&#10;</xsl:text>
                    <xsl:for-each select="SON">

                                <xsl:value-of select="$idN"/>
                                <xsl:text>-&gt;</xsl:text>
                                <xsl:value-of select="@idref"/>
                                <xsl:text>[label=&quot;</xsl:text>
                                <xsl:value-of select="position()"/>
                                <xsl:text>&quot;];&#10;</xsl:text>

                    </xsl:for-each>
                </xsl:for-each>
            </xsl:when>

            <xsl:otherwise>
                <xsl:for-each select="NODE/SON">
                    <xsl:value-of select="$idF"/>
                    <xsl:text>-&gt;</xsl:text>
                    <xsl:value-of select="@idref"/>
                    <xsl:text>[label=&quot;</xsl:text>
                    <xsl:value-of select="position()"/>
                    <xsl:text>&quot;];&#10;</xsl:text>
                </xsl:for-each>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>

    <!--################################################## # Dessine le contenu
        de la forêt une seule fois ################################################## -->
    <xsl:template match="FOREST">
        <xsl:param name="idForest"/>

        <xsl:value-of select="@id"/>
        <xsl:text>[shape=&quot;plaintext&quot;,label=&quot;</xsl:text>
        <xsl:apply-templates select="OUTPUT"/>
        <xsl:text>&quot;</xsl:text>

        <xsl:choose>
            <xsl:when test="@ERROR='true'">
                <xsl:text>,fillcolor=&quot;red&quot;</xsl:text>
            </xsl:when>
            <xsl:when test="@id=$idForest">
                <xsl:text>,fillcolor=&quot;violet&quot;,fontcolor=&quot;white&quot;</xsl:text>
            </xsl:when>
        </xsl:choose>

        <xsl:text>];&#10;</xsl:text>


    </xsl:template>

    <!--################################################## # Dessine le contenu
        de la forêt une seule fois ################################################## -->
    <xsl:template match="FOREST[@empty='true']">
        <xsl:param name="idForest"/>
        <xsl:value-of select="@id"/>
        <xsl:text>[shape=&quot;plaintext&quot;,label=&quot;</xsl:text>
        <xsl:text>&quot;];&#10;</xsl:text>
    </xsl:template>

    <!--################################################## # Dessine le contenu
        de la forêt une seule fois ################################################## -->
  <xsl:template match="OUTPUT">
    <!-- Sélectionnez tous les éléments <S> et produisez-les comme texte -->
    <xsl:apply-templates select="S"/>
  </xsl:template>

  <!-- Correspondance pour l'élément S -->
  <xsl:template match="S">
    <!-- Sortie de la balise <S> en tant que texte -->
    <xsl:value-of select="."/>
    <xsl:text>\n</xsl:text>
  </xsl:template>

  <!-- Ignorer d'autres éléments -->
      <!--################################################## # ################################################## -->
    <xsl:template match="*|text()">
    </xsl:template>

</xsl:stylesheet>
