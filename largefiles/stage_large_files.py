#!/usr/bin/env python
#
# This script moves large files from current directory to the target directory so that they
# are ready for processing with the ucvm_setup.py script
#
# Conditions:
# This script should be run as the same user that is installing ucvm. This
# does not check permissions or ownership of files
#
import os
import sys
from shutil import copyfile

#largefilepath = "." Use if the large files are in the current directory. Otherwise give a path to their location
largefilepath = "/home/scec-00/maechlin/icvm/largefiles"
curpath = "/home/scec-00/maechlin/icvm/test3/UCVMC"

if len(sys.argv) < 2:
  print "Using default as UCVMC install directory"
  print "User can Override the default largefiles directory using the command line like this:"
  print "%stage_large_files.py /home/scec-00/maechlin/icvm/b1/UCVMC"
  src_dir = curpath
else:
  src_dir = str(sys.argv[1])

print src_dir

large_model_list = ["cvms5.tar.gz",
                    "cvms4.tar.gz",
                    "cvms426.tar.gz",
                    "cvmh-15.1.0.tar.gz",
                    "cencal080.tar.gz"]

large_lib_list = ["proj-4.8.0.tar.gz",
                  "fftw-3.3.3.tar.gz",
                  "euclid3-1.3.tar.gz"]

large_etree_list = ["ucvm.e"]

large_ref_list = ["test-grid-lib-1d.ref"]

work_model_dir = src_dir + "/work/model"
print "Work model dir",work_model_dir
lib_dir = src_dir + "/work/lib"
print "Lib dir",lib_dir
model_dir = src_dir + "/model"
print "Model dir", model_dir
test_ref_dir = src_dir + "/test/ref"
print "Test ref dir:",test_ref_dir
#
# Make sure target directories exists, if not create them
#

work_dir = src_dir + "/work"

if not os.path.exists(work_dir):
  print "Creating work_dir: ",work_dir
  os.makedirs(work_dir)

if not os.path.exists(work_model_dir):
  print "Creating work model_dir: ", work_model_dir
  os.makedirs(work_model_dir)

if not os.path.exists(lib_dir):
  print "Creating lib_dir: ", lib_dir
  os.makedirs(lib_dir)

#
# Now move files one by one to destinations
#
for l in large_lib_list:
  local_file = largefilepath + "/" + l 
  target_file = lib_dir + "/" + l
  if not os.path.exists(target_file):
    print "Moving lib:",local_file
    copyfile(local_file,target_file)
    # 
    # remove existing tar file so gzip doesn't ask for permisson
    #
    tarfile = os.path.splitext(os.path.basename(l))[0]
    tarfilepath = lib_dir + "/" + tarfile
    if os.path.exists(tarfilepath):
      print "Removing existing lib tar file",tarfilepath
      os.remove(tarfilepath)
  else:
    print "Target lib file already exists",target_file

for m in large_model_list:
  local_file = largefilepath + "/" + m
  target_file = work_model_dir + "/" + m
  if not os.path.exists(target_file):
    print "Moving model:",local_file
    copyfile(local_file,target_file)
    # 
    # remove existing tar file so gzip doesn't ask for permisson
    #
    tarfile = os.path.splitext(os.path.basename(m))[0]
    tarfilepath = work_model_dir + "/" + tarfile
    if os.path.exists(tarfilepath):
      print "Removing existing model tar file",tarfilepath
      os.remove(tarfilepath)
  else:
    print "Target model file already exists",target_file

for r in large_ref_list:
  local_file = largefilepath + "/" + r
  target_file = test_ref_dir + "/" + r 
  if not os.path.exists(target_file):
    print "Moving ref file:",local_file
    copyfile(local_file,target_file)
  else:
    print "Target model file already exists",target_file

#
# UCVM.e file is staged in the model/ucvm directory
# not the work/ucvm directory. This current script
# works only for ucvm.e due to hardcoded directory name
#
for e in large_etree_list:
  local_file = largefilepath + "/" + e
  target_file = model_dir + "/ucvm/" + e
  if not os.path.exists(target_file):
    print "Moving etree:",local_file
    copyfile(local_file,target_file)
  else:
    print "Target etree file already exists",target_file

print "All required library and model files staged in ucvmc work directories"
sys.exit(0)
