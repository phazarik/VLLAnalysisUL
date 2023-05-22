#!/bin/bash
echo ""
echo "-- Script to create Condor jobs for RHAna--"

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ] || [ -z "$4" ] || [ -z "$5" ] || [ -z "$6" ] || [ -z "$7" ] || [ -z "$8" ]; then
    echo "Missing arguments"
    echo " ./createJobsToCondor.sh  <script.C> <SampleDirName> <SampleDirPath> <other arguments>"
    echo "   ex: ./createJobsToCondor.sh  runana.C TTJets /cms/multilepton/NTUPLES/2015/MC/TTJets/0000 data year lep era mc"
    echo ""
    echo "..exiting!"
    echo ""
    exit 1
fi

echo "Input   .C: "$1
echo "Input Name: "$2
echo "Input  dir: "$3
echo "Input  parameter data: "$4
echo "Input  parameter year: "$5
echo "Input  parameter lep: "$6
echo "Input  parameter era: "$7
echo "Input  parameter mc: "$8
echo ""

inC=$1
inSampleName=$2
inSampleDir=$3
#allargs=$4
#echo $1 $2 $3 $4

MAINDIR=`pwd`
SCRIPTDIR=`pwd`
#LOGDIR="/home/work/alaha1/work/FullRun2/VLLAnalysisUL/CondorOutput"
#LOGDIR="/home/work/phazarik1/work/VLLanalysis/SkimmedSamples"
LOGDIR="/home/work/phazarik1/work/VLLanalysis/CondorOutput"
#`pwd`
#CMSDIR="/home/work/alaha1/work/FullRun2/CMSSW_10_3_1/src"
CMSDIR="/home/work/phazarik1/work/VLLanalysis/CMSSW_10_3_1/src"

# Specify input files here:
inputFolder=$inSampleName
#
datestamp=`date +"%D_%T" | sed 's|/||g' |  sed 's|:||g'`
inputFolder2=$inputFolder"__"$datestamp

condorFile=$SCRIPTDIR"/submitJobsCondor_"$USER"_"$inputFolder2".condor"

if [ -e $condorFile ]
then
    rm -rf $condorFile
fi
touch $condorFile

runScript=$SCRIPTDIR/runJobsCondor_simulation.sh #temporary script execution file
if [ -e $runScript ]
then
    rm -rf $runScript
fi
touch $runScript
chmod a+x $runScript

echo "#!/bin/bash" >> $runScript
echo "export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch" >> $runScript
echo "export COIN_FULL_INDIRECT_RENDERING=1" >> $runScript
echo 'echo $VO_CMS_SW_DIR' >> $runScript
echo 'source $VO_CMS_SW_DIR/cmsset_default.sh' >> $runScript
echo "cd $CMSDIR" >> $runScript
echo 'eval `scramv1 runtime -sh` ' >> $runScript
#echo ' source /opt/apps/root_v5.34.36/bin/thisroot.sh'
#echo "cd $SCRIPTDIR" >> $runScript
# Specify .C macro to be run here:
echo 'root -q -b -l '$inC'\(\"$1\",\"$2\",\"$3\",\"$4\",\"$5\",\"$6\",\"$7\"\)' >> $runScript
echo "" >> $runScript

echo "universe = vanilla" >> $condorFile
#echo '+AccountingGroup = "group_rutgers.'$USER'"' >> $condorFile
echo 'Requirements = (Arch == "X86_64")' >> $condorFile
echo "Executable = $runScript" >> $condorFile
echo "should_transfer_files = YES" >> $condorFile
echo "Notification=never" >> $condorFile
echo "" >> $condorFile
echo "" >> $condorFile

OUTDIR=$LOGDIR/output/$inputFolder2/
#OUTDIR=$LOGDIR
mkdir -p $OUTDIR
LOGDIR=$LOGDIR/log/$inputFolder2/
mkdir -p $LOGDIR
chmod -R 777 $LOGDIR
chmod -R 777 $OUTDIR

#
tmplist=tmp.tmp
#target directory
ls -l $inSampleDir | grep -v total > $tmplist

while read line
do
  base=`echo $line | awk '{split($9,array,"_"); print array[1]}'`
  ofile=`echo $line | awk '{print $9}' | sed 's|.root||g'`
  ifdir=`echo $line | awk '{print $9}'`
  echo "output = $LOGDIR/\$(Cluster)_data_${ifdir}.out" >> $condorFile
  echo "error = $LOGDIR/\$(Cluster)_data_${ifdir}.err" >> $condorFile
  echo "log = $LOGDIR/\$(Cluster)_data_${ifdir}.log" >> $condorFile
  echo "arguments = $inSampleDir/$ifdir $OUTDIR/\$(Cluster)_${ofile}_data.root $4 $5 $6 $7 $8" >> $condorFile
  echo "queue" >> $condorFile
  echo "" >> $condorFile
done < $tmplist
rm -rf $tmplist
cp $condorFile $LOGDIR/
cp $runScript $LOGDIR/
cp ./createJobsToCondor.sh $LOGDIR/
echo ""
echo "Submitting: "$inputFolder
echo ""
echo "To submit jobs:"
echo "condor_submit submitJobsCondor_"$USER"_"$inputFolder2".condor"
echo ""
echo "To watch job progress:"
echo "watch condor_q | grep "$USER
echo ""
echo "Output  log files: "$LOGDIR
echo ""
echo "Output root files: "$OUTDIR
echo ""


eval "condor_submit submitJobsCondor_"$USER"_"$inputFolder2".condor"



