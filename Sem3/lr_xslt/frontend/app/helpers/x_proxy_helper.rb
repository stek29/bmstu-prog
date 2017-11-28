require 'nokogiri'

module XProxyHelper
  BASE_API_URL           = 'http://localhost:3000/?format=xml'.freeze
  XSLT_SERVER_TRANSFORM  = "#{Rails.root}/public/"\
    'server_transform.xslt'.freeze
  XSLT_BROWSER_TRANSFORM = '/browser_transform.xslt'.freeze

  def make_url(m_int)
    BASE_API_URL + "&m=#{m_int}"
  end

  def insert_xslt_instruction(data, transform = XSLT_BROWSER_TRANSFORM)
    doc = Nokogiri::XML(data)

    xslt = Nokogiri::XML::ProcessingInstruction.new(
      doc,
      'xml-stylesheet',
      "type=\"text/xsl\" href=\"#{transform}\""
    )
    doc.root.add_previous_sibling(xslt)

    doc
  end

  def apply_xslt_transform(data, transform = XSLT_SERVER_TRANSFORM)
    doc = Nokogiri::XML(data)
    xslt = Nokogiri::XSLT(File.read(transform))
    xslt.transform(doc)
  end
end
