with import <nixpkgs> {}; {
    cairoprobeEnv = stdenv.mkDerivation {
        name = "cairoprobe-env";
        buildInputs = [ stdenv
                        gcc
                        pkgconfig
                        cairo
                        SDL2
                        ffmpeg-full
                      ];
    };
}
