
command_start_format = '-'
command_end_format = '='
command_len = 78

# file_name = r'C:\Users\MAHMMAD_ALNAJJAR\Documents\python scripts\command_format\text.txt'

with open('text.txt') as read_f:
    lines = read_f.readlines()
    for line in lines:
        rec = line.replace("\n", "")
        total = 0
        for word in rec:
           total +=len(word)
        # print(total)
        if(total % 2) == 0:
            total = (int)(total/2)
            print("//" + command_start_format.replace(command_start_format,command_start_format*(int(command_len/2) - total -1),1) + ' ' + rec + ' ' + command_start_format.replace(command_start_format,command_start_format*(int(command_len/2) - total - 1),1))
        else:
            total = (int)(total/2)
            print("//" + command_start_format.replace(command_start_format,command_start_format*(int(command_len/2) - total -2),1) + ' ' + rec + ' ' + command_start_format.replace(command_start_format,command_start_format*(int(command_len/2) - total - 1),1))
        print("\n",end = "")
        print("//" + command_end_format.replace(command_end_format,command_end_format*int(command_len),1))
        print("\n")
        # print(total)

        
    

        