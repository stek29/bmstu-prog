<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <xsl:choose>
    <xsl:when test="*/error">
      <h2>Error</h2>
      <h3><xsl:value-of select="*/error"/></h3>
    </xsl:when>
    <xsl:otherwise>
      <h2>Result</h2>
      <table class="table">
        <tr>
          <th>M</th>
          <th>M bin</th>
          <th>N bin</th>
          <th>N</th>
        </tr>
        <tr>
          <td id="m-int"><xsl:value-of select="*/num-m/int"/></td>
          <td id="m-bin"><xsl:value-of select="*/num-m/bin"/></td>
          <td id="n-bin"><xsl:value-of select="*/num-n/bin"/></td>
          <td id="n-int"><xsl:value-of select="*/num-n/int"/></td>
        </tr>
      </table>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>
