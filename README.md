python-echoprint
================

A cffi based python interface for the echonest libcodegen library


## Installing

You need the [echoprint-codegen](https://github.com/echonest/echoprint-codegen) dependencies,
then run the following command::

    python setup.py install


## Usage

    import echoprint

    data = echoprint.codegen([...])
    print data['version']
    code = data['code']
    # submit `code` to the echoprint server

The first argument to `echoprint.codegen` an iterable of floats, mono, 11025 Hz. It also takes
an optional second argument hinting the echoprint server from where the sample was taken.
