import cffi

ffi = cffi.FFI()
ffi.set_source('_echoprint', '''
#include <Codegen.h>

typedef struct codegen_handle_t * codegen_handle;

codegen_handle codegen_new(const float *pcm, unsigned int numSamples, int start_offset) {
    Codegen *codegen = new Codegen(pcm, numSamples, start_offset);
    return (codegen_handle) codegen;
}

const char* codegen_get_code_string(codegen_handle handle) {
    return ((Codegen*) handle)->getCodeString().c_str();
}

int codegen_get_num_codes(codegen_handle handle) {
    return ((Codegen*) handle)->getNumCodes();
}

double codegen_get_version(codegen_handle handle) {
    return ((Codegen*) handle)->getVersion();
}

void codegen_free(codegen_handle handle) {
    delete (Codegen*)handle;
}

''', sources=[
    'libcodegen/AudioBufferInput.cxx',
    'libcodegen/AudioStreamInput.cxx',
    'libcodegen/Base64.cxx',
    'libcodegen/Codegen.cxx',
    'libcodegen/Fingerprint.cxx',
    'libcodegen/MatrixUtility.cxx',
    'libcodegen/Metadata.cxx',
    'libcodegen/SubbandAnalysis.cxx',
    'libcodegen/Whitening.cxx'
], source_extension='.cxx', include_dirs=[
    '/usr/include/taglib', 'libcodegen'
], libraries=['tag', 'z', 'pthread'])

ffi.cdef('''
typedef struct codegen_handle_t * codegen_handle;

codegen_handle codegen_new(const float *pcm, unsigned int numSamples, int start_offset);
const char* codegen_get_code_string(codegen_handle handle);
int codegen_get_num_codes(codegen_handle handle);
double codegen_get_version(codegen_handle handle);
void codegen_free(codegen_handle handle);
''')


if __name__ == '__main__':
    ffi.compile()


