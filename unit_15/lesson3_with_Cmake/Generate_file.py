def create_header_file(filename, ifndef_name, header_text):
    with open(filename, 'w') as file:
        file.write(f'#ifndef {ifndef_name}\n')
        file.write(f'#define {ifndef_name}\n\n')
        file.write(header_text)
        file.write(f'\n#endif // {ifndef_name}\n')

# تعريف النص الذي ترغب في وضعه في الملف
header_text = '''
// قم بإضافة الكود الخاص بك هنا
'''

# تعريف اسم الملف
file_name = 'header_file.h'

# تعريف اسم قسم ifndef
ifndef_name = 'HEADER_FILE_H'

# استدعاء الدالة لإنشاء الملف
create_header_file(file_name, ifndef_name, header_text)
