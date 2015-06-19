import _echoprint


def codegen(data, start_offset=0):
    try:
        length = len(data)
    except TypeError:
        # in case we got an iterator
        data = list(data)
        length = len(data)

    # 191 seems arbitrary and it kind of is ...
    # the value was found by repeatedly testing
    if length < 191:
        raise ValueError('not enough data')

    buf = _echoprint.ffi.new('float[]', data)
    handle = _echoprint.lib.codegen_new(buf, length, start_offset)
    version = _echoprint.lib.codegen_get_version(handle)
    code_string = _echoprint.ffi.string(
        _echoprint.lib.codegen_get_code_string(handle)
    )
    _echoprint.lib.codegen_free(handle)

    # just to match the non-cffi API
    return {
        'code': code_string,
        'version': version
    }
