import os
import subprocess

def main():
    for file in 'ten1.txt        ten1000ants.txt ten3.txt        ten5.txt        ten7.txt        ten9.txt        tenants.txtC ten10.txt       ten2.txt        ten4.txt        ten6.txt        ten8.txt        tenants.txt'.split():
        print(file)
        with open(os.path.join('lem-in-checker', file), 'r', encoding='utf-8') as f:
            fl = 0
            dct = dict()
            for line in f.readlines():
                if line.strip() == '##start':
                    fl = 1
                elif line.strip() == "##end":
                    fl = 2
                elif fl == 1:
                    start = line.split()[0].strip()
                    fl = 0
                elif fl == 2:
                    end = line.split()[0].strip()
                    fl = 0
                elif len(line.split()) == 1 and '-' in line:
                    if line.split('-')[0].strip() in dct:
                        dct[line.split('-')[0].strip()].append(line.split('-')[1].strip())
                    else:
                        dct[line.split('-')[0].strip()] = [line.split('-')[1].strip()]
                    if line.split('-')[1] .strip()in dct:
                        dct[line.split('-')[1].strip()].append(line.split('-')[0].strip())
                    else:
                        dct[line.split('-')[1].strip()] = [line.split('-')[0].strip()]
        with open(os.path.join('lem-in-checker', file), 'r', encoding='utf-8') as f:
            popen = subprocess.Popen("./lem-in", stdin=f, stdout=subprocess.PIPE)
            output = popen.stdout.read().decode("utf-8") 
        prev_line = ''
        for line in output.split():
            if line == 'start':
                line = start
            elif line == 'end':
                line = end
            if prev_line != end and prev_line != '':
                if not (prev_line in dct and line in dct[prev_line]) and not (line in dct and prev_line in dct[line]):
                    print("ERRRRRROR")
                    print(prev_line, line)
            prev_line = line

if __name__ == '__main__':
    main()