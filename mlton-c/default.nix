with import <nixpkgs> {}; {
    mltoncEnv = stdenv.mkDerivation {
        name = "mltonc-env";
        buildInputs = [ stdenv
                        gcc
                        pkgconfig
                        mlton
                      ];
    };
}
