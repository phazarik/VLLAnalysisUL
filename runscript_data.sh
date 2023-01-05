#!/bin/sh
JOBNAME="Skimmed2mu_Basic_Jan05"
SAMPLE=(
    "A"
    "B"
    "C"
    "D"
)

echo ""
echo "###################################################################################"
for S in "${SAMPLE[@]}"; do
    echo "./createJobsToCondor.sh /home/work/phazarik1/work/VLLanalysis/VLLAnalysisUL/archive/prachu/skimmed_study/runana.C "$JOBNAME"_SingleMuon_SingleMuon_"$S"__sample /home/work/phazarik1/work/VLLanalysis/SkimmedSamples/Skimmed2018/VLLAna_2muSkimmed_Dec19/UL2018Data/SingleMuon/SingleMuon"$S"/ 1 2018 mu Z wz"
    echo""
done
echo "###################################################################################"
echo "Run these scripts"
echo ""
