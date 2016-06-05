#! /usr/bin/env python
#------------------------------------------------------------------------------
#
# Name: cafe_depend.py
#
# Purpose: Analyze link dependencies between caf packages.
#
# Usage: cafe_depend.py
#
# This script analyzes link dependencies among the several caf packages
# by analyzing shared libraries.  Shared libraries are looked for in
# a private test release ($SRT_PRIVATE_CONTEXT), if defined, and in the
# public release ($SRT_PUBLIC_CONTEXT).
#
# The output from this script can be cut-and-pasted into cafe_sam/bin/cafe.cpp.
#
#------------------------------------------------------------------------------

# List of package to include in the analysis.
# Packages cafe, cafe_sam, tmb_tree, met_util, and kinem_util are not
# included because they are linked into the cafe executable.
# This list includes all packages listed on the vjets_cafe web page, and more.
# Not all of these packages (currently) have shared libraries.  Those
# not having shared libraries are ignored.

all_pkgs = ('vjets_cafe', 'caf_util', 'caf_mc_util', 'emid_cuts',
            'EMresolution_cafe', 'caf_eff_utils', 'eff_utils', 'caf_trigger',
            'lumi_profiles', 'beamposition', 'caf_mc_info', 'emid_eff',
            'muid_eff', 'jetid_eff', 'tauid_eff', 'dq_defs', 'caf_dq',
            'dq_util', 'btags_cert', 'btags_cert_caf', 'd0root_btag',
            'd0root_analysis', 'd0root_sltnn', 'd0root_slt', 'd0root_jlip',
            'd0root_csip', 'd0root_nnbtag', 'd0root_mva_btagger',
            'd0root_tmbtree', 'd0root_example_caf', 'bc_csiptagger',
            'caf_cert', 'bdt_reader', 'jetcorr', 'tau_tmb', 'tmb2ttau')

# Imports

import sys, os

# Function to test whether a file exists.

def exist_file(filename):
    try:
        file = open(filename)
        file.close()
        return 1
    except:
        return 0

# Recursive function to return the full list of dependent packages for a
# given package.  Crashes if a circular dependence is found.

def full_depends(orig_pkg, pkg, depends):
    result = []

    # Find direct dependencies.
    
    apkgs = depends[pkg].keys()
    for apkg in apkgs:
        if not apkg in result:
            result.append(apkg)

        # Find indirect dependencies.
            
        bpkgs = full_depends(orig_pkg, apkg, depends)
        for bpkg in bpkgs:
            if bpkg == orig_pkg:
                print 'Circular dependence between %s and %s' % (bpkg, orig_pkg)
                sys.exit(1)
            if not bpkg in result:
                result.append(bpkg)
    return result

# Main function.

def main(argv):

    # Get SRT environment variables.

    try:
        public = os.environ['SRT_PUBLIC_CONTEXT']
    except:
        print 'Environment variable SRT_PUBLIC_CONTEXT is not defined.'
        sys.exit(1)
    try:
        private = os.environ['SRT_PRIVATE_CONTEXT']
    except:
        private = ''
    try:
        subdir = os.environ['SRT_SUBDIR']
    except:
        print 'Environment variable SRT_SUBDIR is not defined.'
        sys.exit(1)

    # Find shared libraries.

    shlibs = {}
    
    for pkg in all_pkgs:

        # Search for shared library for this package.

        shlib_ok = 0
        shlib = ''
        if private != '':
            shlib = private + '/shlib/' + subdir + '/lib' + pkg + '.so'
            if exist_file(shlib):
                shlib_ok = 1
        if not shlib_ok:
            shlib = public + '/shlib/' + subdir + '/lib' + pkg + '.so'
            if exist_file(shlib):
                shlib_ok = 1

        if shlib_ok:
            shlibs[pkg] = shlib
        else:
            print "Shared library not found for package %s" % pkg

    # Find defined symbols for each shared library.

    defined = {}
    for pkg in shlibs.keys():
        print 'Reading defined symbols for package %s' % pkg
        defined[pkg] = {}
        shlib = shlibs[pkg]

        # Use shell command "nm."
        
        for line in os.popen("nm -Bg %s | grep ' T ' | awk '{print $3}'" % shlib):
            symbol = line.rstrip()
            defined[pkg][symbol] = 0
        #print ' T: %d' % len(defined[pkg])
        
    # Find undefined symbols.  Find direct dependencies.

    depends = {}
    for pkg in shlibs.keys():
        print 'Reading undefined symbols for package %s' % pkg
        depends[pkg] = {}
        shlib = shlibs[pkg]

        # Use shell command "nm."
        
        for line in os.popen("nm -Bg %s | grep ' U ' | awk '{print $2}'" % shlib):
            symbol = line.rstrip()
            for def_pkg in shlibs.keys():
                if defined[def_pkg].has_key(symbol):
                    depends[pkg][def_pkg] = 0
        #print depends[pkg].keys()

    # Find expanded dependencies to all levels.
    # If there are circular dependencies, the script will crash here.

    expanded_depends = {}
    for pkg in shlibs.keys():
        expanded_depends[pkg] = {}
        dep_pkgs = full_depends(pkg, pkg, depends)
        for dep_pkg in dep_pkgs:
            expanded_depends[pkg][dep_pkg] = 0
        #print pkg, expanded_depends[pkg].keys()

    # Find a minimal set of dependencies such that dependent packages
    # are removed from listed dependencies.

    minimal_depends = {}
    for pkg in shlibs.keys():
        remove = []
        minimal_depends[pkg] = {}
        for pkg1 in expanded_depends[pkg].keys():
            for pkg2 in expanded_depends[pkg].keys():
                if expanded_depends[pkg1].has_key(pkg2):
                    if not pkg2 in remove:
                        remove.append(pkg2)
                if expanded_depends[pkg2].has_key(pkg1):
                    if not pkg1 in remove:
                        remove.append(pkg1)
        for dep_pkg in expanded_depends[pkg].keys():
            if not dep_pkg in remove:
                minimal_depends[pkg][dep_pkg] = 0

        # Generate printout in a form compatible with cafe_sam/bin/cafe.cpp.

        for dep_pkg in minimal_depends[pkg].keys():
            print '      _dependencies["%s"].push_back("%s");' % (pkg, dep_pkg)
                    
# Main program.

if __name__ == '__main__':
    sys.exit(main(sys.argv))
