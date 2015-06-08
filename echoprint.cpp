#include <Codegen.h>
#include <Python.h>
#include <stdio.h>

static PyObject * echoprint_codegen(PyObject *self, PyObject *args) {
    PyObject *py_samples;
    int start_offset = 0;
    PyObject *item;
    float *samples;
    uint num_samples;
    uint i;
    Codegen *pCodegen;
    PyObject *result;
    
    if (!PyArg_ParseTuple(args, "O|i", &py_samples, &start_offset)) {
        return NULL;
    }

    py_samples = PySequence_Fast(py_samples, "expected a sequence");
    num_samples = PySequence_Length(py_samples);
    samples = new float[num_samples];

    for (i = 0; i < num_samples; i++) {
        item = PySequence_Fast_GET_ITEM(py_samples, i);
        if (!PyFloat_Check(item)) {
            delete[] samples;
            PyErr_SetString(PyExc_TypeError, "expected sequence of floats");
            return NULL;
        }
        samples[i] = (float)PyFloat_AsDouble(item);
    }
    Py_DECREF(py_samples);

    pCodegen = new Codegen(samples, num_samples, start_offset);
    result = Py_BuildValue("{s:s,s:f}",
        "code", pCodegen->getCodeString().c_str(),
        "version", pCodegen->getVersion()
    );
    delete pCodegen;
    delete[] samples;
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


