#!/usr/bin/env python3

##
#  @file plot_cross_section_by_elevation.py
#  @brief Plots a cross section using command-line parameters.
#  @author
#  @version 
#
#  Plots a cross section given a set of command-line parameters.

from pycvm import ElevationCrossSection, UCVM, VERSION, UCVM_CVMS, Point, ask_number, ask_path, ask_file, get_user_opts
import getopt, sys, os
import json
import pdb

## Prints usage statement.
def usage():
    print("Plots a cross-section given two latitude, longitude points, one or two elevations,")
    print("the CVM to plot, and a couple of other settings.")
    print("\nValid arguments:")
    print("\t-s, --starting: starting elevation for cross-section (meters)")
    print("\t-e, --ending: ending elevation for cross-section (meters)")
    print("\t-h, --horizontal: horizontal spacing for cross-section (meters)")
    print("\t-v, --vertical: vertical spacing for cross-section (meters)")
    print("\t-d, --datatype: either 'vs', 'vp', 'density', or 'poisson', without quotation marks")
    print("\t-c, --cvm: one of the installed CVMs")
    print("\t-z, --zrange: optional Z-range for elygtl:ely (e.g. -z 0,350)")
    print("\t-a, --scale: color scale, either 's' for smooth, 'd' for discretized or 'b' for bi-color scale, without quotes")
    print("\t-g, --gate: optional gate value for bi-color scale gate")
    print("\t-b, --origin: origin latitude, longitude from which to start plot (e.g. 34,-118)")
    print("\t-u, --destination: destination latitude, longitude to end plot (e.g. 35,-117)")
    print("\t-f, --datafile: optional input filename")
    print("\t-o, --outfile: optional png output filename")
    print("\t-t, --title: optional plot title")
    print("\t-H, --help: optional display usage information")
    print("\t-i, --installdir: optional UCVM isntall directory")
    print("\t-n, --configfile: optional UCVM configfile")
    print("UCVM %s\n" % VERSION)

ret_val = get_user_opts({"b,origin":"lat1,lon1", \
			 "u,destination":"lat2,lon2", \
                         "s,starting":"starting_elevation", \
			 "e,ending":"ending_elevation", \
                         "d,datatype":"data_type", \
			 "c,cvm":"cvm", \
			 "h,horizonatal":"horizontal_spacing", \
			 "v,vertical":"vertical_spacing", \
                         "z,zrange,o":"zrange1,zrange2", \
			 "a,scale": "color", \
			 "g,gate,o": "gate", \
			 "f,datafile,o":"datafile", \
                         "o,outfile,o":"outfile", \
                         "t,title,o":"title", \
                         "H,help,o":"", \
                         "i,installdir,o":"installdir", \
                         "n,configfile,o":"configfile" })

meta = {}

if ret_val == "bad":
    usage()
    exit(1)
elif ret_val == "help":
    usage()
    exit(0)
elif len(ret_val) > 0:
    print("Using parameters:\n")
    for key, value in ret_val.iteritems():
        print(key , " = " , value)
        meta[key] = value
        try:
            float(value)
            exec("%s = float(%s)" % (key, value))
        except StandardError, e:
            if value is None:
                exec("%s = %s" % (key, value))
            else:
                exec("%s = '%s'" % (key, value))
else: 
    print("")
    print("Plot Cross-Section - UCVM %s" % VERSION)
    print("")
    print("This utility helps you plot a cross-section across the earth for one of the CVMs")
    print("that you installed with UCVM.")
    print("")
    print("In order to create the plot, you must first specify the starting point.")
    print("")

    lon1 = ask_number("Please enter the origin longitude from which the plot should start: ")
    lat1 = ask_number("Next, enter the origin latitude from which the plot should start: ")
    lon2 = ask_number("Enter the destination longitude where the plot should end: ")
    lat2 = ask_number("Enter the destination latitude where the plot should end: ")
    meta['lon1']=lon1
    meta['lon2']=lon2
    meta['lat1']=lat1
    meta['lat2']=lat2

    starting_elevation = 0 
    starting_elevation = ask_number("Please enter the elevation, in meters, at which you would like \n" + \
                                    "this cross-section to start: ")
    meta['starting_elevation']=starting_elevation

    ending_elevation = 0 
    ending_elevation = ask_number("Please enter the elevation, in meters, at which you would like \n" + \
                                  "this cross-section to end: ")

    if ending_elevation >= starting_elevation:
        print("Error: the bottom, ending elevation must be less than the starting elevation.")
    meta['ending_elevation']=ending_elevation
 
    horizontal_spacing = -1
    while horizontal_spacing < 0:
        horizontal_spacing = ask_number("Please enter the horizontal spacing, in meters, for the plot: ")
        if horizontal_spacing < 0:
            print("Error: the spacing must be a positive number.")
    meta['horizontal_spacing']=horizontal_spacing

    vertical_spacing = -1
    while vertical_spacing < 0:
        vertical_spacing = ask_number("Please enter the vertical spacing, in meters, for the plot: ")
        if vertical_spacing < 0:
            print("Error: the spacing must be a positive number.")   
    meta['vertical_spacing']=vertical_spacing

    data_type = ""
    while data_type != "vs" and data_type != "vp" and data_type != "density":
        data_type = raw_input("What would you like to plot (either vp, vs, or density): ")
        data_type = data_type.lower().strip()
    
        if data_type != "vs" and data_type != "vp" and data_type != "density":
            print("Error: you must select either 'vp', 'vs', 'density' (without quotation marks).")
    meta['mproperty']=data_type

    counter = 1
    corresponding_cvm = []
    installdir = None
    configfile = None

    # Ask if a different installdir should be  used
    cwd = os.getcwd()
    installdir = ask_path("Do you want to use different UCVM install directory", cwd+"/..")
    # Ask if a different ucvm.conf should be  used
    configfile = ask_file("Do you want to use different ucvm.conf file", cwd+"/../ucvm.conf")

    # Ask which CVMs to use.
    print("From which CVM would you like this data to come:")

    # Create a new UCVM object.
    u = UCVM(install_dir=installdir, config_file=configfile)

    for cvm in u.models:
        cvmtoprint = cvm
        if cvm in UCVM_CVMS:
            cvmtoprint = UCVM_CVMS[cvm]
        corresponding_cvm.append(cvm)
        print("\t%d) %s" % (counter, cvmtoprint))
        counter += 1
    
    cvm_selected = -1
    while cvm_selected < 0 or cvm_selected > counter:
        cvm_selected = int(ask_number("\nSelect the CVM: ")) - 1
    
        if cvm_selected < 0 or cvm_selected > counter:
            print("Error: the number you selected must be between 1 and %d" % counter)

    cvm_selected = corresponding_cvm[cvm_selected]
    meta['cvm']=cvm_selected

    # We will offer two color options. Discretized or smooth. But, we'll only offer red-blue for now.
    gate = 2.5
    color = ""

    while color != "s" and color != "d" and color != "b" :
        print("")
        color = raw_input("Finally, would you like a descritized or smooth color scale\n(enter 'd' for discrete, 's' for smooth, 'b' for bi-color): ")
        color = color.strip()
    
        if color != "s" and color != "d" and color != "b":
            print("Please enter 'd' (without quotation marks) for a discrete color bar and 's' (without quotation")
            print("marks) for a smooth color scale and 'b' (without quotation marks) for bi-color scale.")
    meta['gate']=gate
    meta['color']=color

# Now we have all the information so we can actually plot the data.
print("")
print("Retrieving data. Please wait...")

###################################################################################
# Generate the horizontal slice.
d = ElevationCrossSection(Point(lon1, lat1, elevation=starting_elevation), Point(lon2, lat2, elevation=starting_elevation), meta)
d.plot()
