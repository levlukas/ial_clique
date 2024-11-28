def czech_to_latex(input_string):
    utf_to_latex = {
        'á': "\\'a", 'č': "\\v{c}", 'ď': "\\v{d}", 'é': "\\'e",
        'ě': "\\v{e}", 'í': "\\'i", 'ň': "\\v{n}", 'ó': "\\'o",
        'ř': "\\v{r}", 'š': "\\v{s}", 'ť': "\\v{t}", 'ú': "\\'u",
        'ů': "\\r{u}", 'ý': "\\'y", 'ž': "\\v{z}",
        'Á': "\\'A", 'Č': "\\v{C}", 'Ď': "\\v{D}", 'É': "\\'E",
        'Ě': "\\v{E}", 'Í': "\\'I", 'Ň': "\\v{N}", 'Ó': "\\'O",
        'Ř': "\\v{R}", 'Š': "\\v{S}", 'Ť': "\\v{T}", 'Ú': "\\'U",
        'Ů': "\\r{U}", 'Ý': "\\'Y", 'Ž': "\\v{Z}"
    }

    translated = ''.join(utf_to_latex.get(char, char) for char in input_string)
    return translated

def process_files(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as infile:
        input_text = infile.read()
    
    latex_text = czech_to_latex(input_text)
    
    with open(output_file, 'w', encoding='utf-8') as outfile:
        outfile.write(latex_text)


input_filename = 'input.txt'   
output_filename = 'output.txt' 

process_files(input_filename, output_filename)
