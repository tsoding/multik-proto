with import <nixpkgs> {}; {
    multikProtoEnv = stdenv.mkDerivation {
        name = "multik-proto-env";
        buildInputs = [ stdenv
                        gcc
                        pkgconfig
                        cairo
                        SDL2
                        ffmpeg-full
                        mlton
                      ];
    };
}
