{
    "targets": [{
        "target_name": "backend",
        "sources": [
            "../cpp-backend/backend.cpp",
            "../cpp-backend/main.cpp",
        ],
        "cflags_cc": [
            "-std=c++17"
        ],   
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}