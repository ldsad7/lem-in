import os
import subprocess

def main():
    for file in 'bigs.txt   bigs12.txt bigs15.txt bigs18.txt bigs20.txt bigs23.txt bigs26.txt bigs29.txt bigs31.txt bigs34.txt bigs37.txt bigs4.txt  bigs6.txt  bigs9.txt bigs10.txt bigs13.txt bigs16.txt bigs19.txt bigs21.txt bigs24.txt bigs27.txt bigs3.txt  bigs32.txt bigs35.txt bigs38.txt bigs40.txt bigs7.txt  bigsup.txt bigs11.txt bigs14.txt bigs17.txt bigs2.txt  bigs22.txt bigs25.txt bigs28.txt bigs30.txt bigs33.txt bigs36.txt bigs39.txt bigs5.txt  bigs8.txt'.split():
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