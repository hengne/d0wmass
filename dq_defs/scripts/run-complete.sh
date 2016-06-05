#! /bin/sh
#
# query sam db to find files from run ${1} which do not have descendent
# files. The latter would be incomplete.
#

if test $# -lt 1
then
  echo ""
  echo " -> usage: run-complete.sh <run number>| -f <input file>"
  echo ""
  exit 1
fi

ifile=""
irun="${1}"

while getopts "f" opt
do
  case ${opt} in
    f)
      ifile=${2}
      ;;
    *)
      echo "Unrecognized option ${opt}"
      ;;
  esac
done

if test "x${ifile}" = "x"
then
  echo "===== ${1}"

  sam translate constraints --dim="(run_number ${1} and data_tier raw and \
  trig_config_type physics and physical_datastream_name all_%) minus \
  (file_analyzed > 0 and (version_analyzed p20.08.01,p20.07.01) and \
  (appl_name_analyzed d0reco,recon_root))" 
else
  while read line
  do
    echo "===== ${line}"
    if test "`echo ${line} | cut -c1`" != "#"
    then
      sam translate constraints --dim="(run_number ${line} and data_tier \
      raw and trig_config_type physics and physical_datastream_name all_%) \
       minus (file_analyzed > 0 and (version_analyzed p20.08.01,p20.07.01) \
       and (appl_name_analyzed d0reco,recon_root))" 
    fi
  done < ${ifile}
fi
