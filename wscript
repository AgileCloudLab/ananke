#! /usr/bin/env python
# encoding: utf-8
from waflib.Tools.compiler_cxx import cxx_compiler

import subprocess

import sys
import os

APPNAME = "ananke"
VERSION = "1.0.0"


cxx_compiler["linux"] = ["clang++"]



def options(opt):
    opt.load("compiler_cxx")


def options(opt):
    opt.load("compiler_cxx")

def configure(ctx) :
    # TODO FIGURE OUT HOW THIS WORKS, cause it is bloody awesome
    #cnf.check(lib=["cryptopp", "pqxx", "pq"])

    ctx.load("compiler_cxx")
    ctx.env.append_value("CXXFLAGS", ["-std=c++17", "-Wall", "-Werror", "-Wextra", "-O3"])         
        
    ctx.env.append_value("LINKFLAGS", "-pthread")            

def build(bld):

    lib = ["fmt", "z", "bz2"]
    
    bld(name = "{}_includes".format(APPNAME),
        includes="./src",
        export_includes="./src")

    bld.stlib(name = "{}".format(APPNAME),
        features = "cxx cxxstlib",
        target="{}".format(APPNAME),
        includes="../src",
        source=bld.path.ant_glob("src/{}/**/*.cpp".format(APPNAME)),
        use=["{}_includes".format(APPNAME)]
    )

    bld.recurse("test/test_gzip")
    bld.recurse("test/test_bzip2")
    bld.recurse("test/test_ananke")

    bld.recurse("benchmark/bzip2")
    bld.recurse("benchmark/gzip")    

    

def test(t):
    run_tests("build/test")

def doc(dc):
    generate_documentation()


## Helper functions

# run_tests
# finds all test locate in the sub dirs of base dir and executes them
# @param base_dir your test folder 
def run_tests(base_dir):

    os.mkdir("test_out")
    platform = sys.platform
    if not base_dir.endswith("/"):
        base_dir = base_dir + "/"
    
    exec_cmd = "./" + base_dir

    for dir in os.listdir(base_dir):
        current_dir = base_dir + dir

        for proc in os.listdir(current_dir):
            if not proc.endswith(".o"):
                cproc = "./" + current_dir + "/" + proc
                os.system(cproc)
    subprocess.call(["rm", "-r", "test_out"], encoding="utf-8")

# Generate documentation for
# @param doc_tool the name of the document tool command
# @param config_file is the name of a potential config file
# @param params is a list of string of the parameters for the document tool
def generate_documentation(doc_tool="doxygen", params=None, config_file=None):

    param_str = ""
    if params:
        for param in params:
            param_str = param_str + param + " "


    cmd = doc_tool + " "
    
    if len(param_str) == 0:
        cmd = cmd + param_str

    if config_file:
        cmd = cmd + config_file
    
    os.system(cmd)

    
    
