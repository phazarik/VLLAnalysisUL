import os
import time #for calculating how much time taken
start_time = time.time()

signal = ['100', '125', '150', '200', '250', '300', '350', '400']

for mass in signal:
    print(f'\n\033[93mRunning for VLLM{mass} .... \033[0m')
    arguments = f'"/home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmer/skimmed_signal/VLL{mass}_skimmed.root", "outputs/hst_VLL{mass}.root", "0", "2018", "mu", "Z", "wz"'
    processline = f"root -q -b -l 'runana.C({arguments})'"
    #print(processline)
    os.system(processline)

end_time = time.time()
time_taken = end_time-start_time

print('\n---------------------------------------------------------')
print(f'\033[93mtime taken : {time_taken:.2f} seconds\033[0m')
print('---------------------------------------------------------')
