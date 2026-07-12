{
  description = "Aegis UEFI bootloader";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      mkShellFor = system:
        let
          pkgs = import nixpkgs { inherit system; };
          ovmfPkg = if pkgs ? ovmf then pkgs.ovmf else null;

          commonPackages = [
            pkgs.clang
            pkgs.lld
            pkgs.gnumake
            pkgs.pkg-config
            pkgs.qemu
            pkgs.dosfstools
            pkgs.mtools
          ];

          extraPackages = (if system == "x86_64-linux" then [ pkgs.gnu-efi ] else [ ]) ++ (if ovmfPkg != null then [ ovmfPkg ] else []);
          ovmfCode = if ovmfPkg != null then "${ovmfPkg}/share/ovmf/OVMF_CODE.fd" else "";
          ovmfVars = if ovmfPkg != null then "${ovmfPkg}/share/ovmf/OVMF_VARS.fd" else "";
        in
        pkgs.mkShell {
          packages = commonPackages ++ extraPackages;
          shellHook = builtins.concatStringsSep "\n" (builtins.filter (x: x != "") [
            (if ovmfPkg != null then "export OVMF_CODE=\"${ovmfCode}\"" else "")
            (if ovmfPkg != null then "export OVMF_VARS=\"${ovmfVars}\"" else "")
            ''export QEMU_SYSTEM_X86_64="${pkgs.qemu}/bin/qemu-system-x86_64"''
            ''export MKFS_FAT="${pkgs.dosfstools}/bin/mkfs.fat"''
            ''export MTOOLS="${pkgs.mtools}/bin"''
            ''export PATH="$MTOOLS:$PATH"''
            (if system == "x86_64-linux" then ''export PKG_CONFIG_PATH="${pkgs.gnu-efi}/lib/pkgconfig:$PKG_CONFIG_PATH"'' else "")
          ]);
        };
    in {
      devShells.default = mkShellFor "aarch64-darwin";
      devShells.x86_64-linux.default = mkShellFor "x86_64-linux";
      devShells.aarch64-darwin.default = mkShellFor "aarch64-darwin";
    };
}
