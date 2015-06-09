#include <Codegen.h>
#include <Python.h>
#include <stdio.h>

static PyObject * echoprint_codegen(PyObject *self, PyObject *args) {
    PyObject *py_samples;
    int start_offset = 0;
    PyObject *item;
    //float *samples;
    std::vector<float> samples;
    unsigned int num_samples;
    Codegen *pCodegen;
    PyObject *result;
    
    if (!PyArg_ParseTuple(args, "O|i", &py_samples, &start_offset)) {
        return NULL;
    }

    if (PyObject_HasAttrString(py_samples, "__len__")) {
        samples.reserve(PyObject_Size(py_samples));
    }

    py_samples = PyObject_GetIter(py_samples);
    if (py_samples == NULL) {
        PyErr_SetString(PyExc_TypeError, "samples is not iterable");
        return NULL;
    }

    for (num_samples = 0; item = PyIter_Next(py_samples); ++num_samples) {
        if (!PyFloat_Check(item)) {
            Py_DECREF(item);
            PyErr_SetString(PyExc_TypeError, "expected sequence of floats");
            return NULL;
        }

        samples.push_back((float)PyFloat_AsDouble(item));
        Py_DECREF(item);
    }
    Py_DECREF(py_samples);

    // prevent segfault in codegen, also &samples.front()
    if (num_samples == 0) {
        Py_RETURN_NONE;
    }

    pCodegen = new Codegen(&samples.front(), num_samples, start_offset);
    result = Py_BuildValue("{s:s,s:f}",
        "code", pCodegen->getCodeString().c_str(),
        "version", pCodegen->getVersion()
    );
    delete pCodegen;
    return result;
}

static PyMethodDef echoprint_methods[] = {
    {"codegen", echoprint_codegen, METH_VARARGS,
     "Generates a echoprint code for a list of floating point PCM data sampled at 11025 Hz and mono. "
     "Optionally takes a second integer argument to hint the server "
     "on where the sample is taken from in the original file if known."
    },
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initechoprint(void)
{
    (void) Py_InitModule("echoprint", echoprint_methods);
}


