#!/usr/bin/env python
from setuptools import setup


setup(
    name='python-echoprint',
    version='0.1',
    description='A Python library for Echonest\'s Echoprint music identification service',
    author='Dav1d',
    url='https://github.com/Dav1dde/python-echoprint',
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["echoprint_build.py:ffi"],
    install_requires=["cffi>=1.0.0"],
    py_modules=['echoprint']
)

