import xlsxwriter

workbook_plus = xlsxwriter.Workbook('plus.xlsx')
workbook_minus = xlsxwriter.Workbook('minus.xlsx')
workbook_multiply = xlsxwriter.Workbook('multiply.xlsx')

worksheet_plus = workbook_plus.add_worksheet()
worksheet_minus = workbook_minus.add_worksheet()
worksheet_multiply = workbook_multiply.add_worksheet()

for i in range(0, 10):
    for j in range(0, 10):
        worksheet_plus.write(i, j, "{}+{}={}".format(i, j, i+j))
        worksheet_minus.write(i, j, "{}-{}={}".format(i, j, i-j))
        worksheet_multiply.write(i, j, "{}*{}={}".format(i, j, i*j))

workbook_plus.close()
workbook_minus.close()
workbook_multiply.close()
