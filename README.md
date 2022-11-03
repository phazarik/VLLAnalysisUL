# VLLAnalysisUL

#### How to submit condor job:
---
###### Check all the settings before submitting jobs
```
python3 submitCondorJobs.py --jobname give_a_jobname --codedir path_to_VLLAna.C --dryrun yes
```

###### Submit One Job to check
```
python3 submitCondorJobs.py --jobname give_a_jobname --codedir path_to_VLLAna.C --test yes
```

###### Submit Condor Jobs:
```
python3 submitCondorJobs.py --jobname give_a_jobname --codedir path_to_VLLAna.C
```
