require 'nokogiri'
xslt = Nokogiri::XSLT(File.read('transform.xslt'))

suc_doc = Nokogiri::XML(File.read('response.xml'))
File.write('response.html', xslt.transform(suc_doc))

err_doc = Nokogiri::XML(File.read('error.xml'))
File.write('error.html', xslt.transform(err_doc))
