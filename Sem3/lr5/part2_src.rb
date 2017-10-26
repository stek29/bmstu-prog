def fix_string(str)
  words = str.split

  words.collect! do |el|
    el[0] = 'т' if el[0] == 'н'
    el[-1] = 'е' if el[-1] == 'о'
    el
  end

  words.join(' ')
end
