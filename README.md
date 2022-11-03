#  Intel® Graphics Driver Backports for Linux® OS (intel-gpu-i915-backports)

This branch provides i915 driver source code backported for SUSE® Linux® Enterprise Server to enable intel discrete GPUs support.

We are using [backport project](https://backports.wiki.kernel.org/index.php/Main_Page) to generate out of tree i915 kernel module source codes.

This repo is a code snapshot of particular version of backports and does not contain individual git change history.

# Branches
 suse/main will point to the currently supported version of SUSE® Linux® Enterprise Server.
 
 We will add a new branch suse/sles<x.y> whenever a version is deprecated or moved to the maintenance phase.
 
 **NOTE: FOR SLES15 SP4, PLEASE FOLLOW [backport/main](https://github.com/intel-gpu/intel-gpu-i915-backports/tree/backport/main) Branch.** 

# Supported Version/kernel
  our current backport is based on **SUSE® Linux® Enterprise Server 15SP3**. We are using the header of the latest available kernel at the time of backporting. However, it may not be compatible with the latest version at the installation time.
  Please refer [Version](https://github.com/intel-gpu/intel-gpu-i915-backports/blob/suse/main/versions)
  file to check the BASE_KERNEL_NAME. It will point to the kernel version which is being used during backporting.

 In case of an issue with the latest kernel, please install the kernel version pointed by BASE_KERNEL_NAME.

    sudo zypper ref -s && sudo zypper install -y kernel-default-<BASE_KERNEL_VERSION> \
    kernel-syms-<BASE_KERNEL_VERSION>

    example:
        sudo zypper ref -s && sudo zypper install -y kernel-default-5.3.18-150300.59.49.1 \
        kernel-syms-5.3.18-150300.59.49.1
 
# Prerequisite
we have dependencies on the following packages
  - dkms
  - make
  - linux-glibc-devel
  - lsb-release
  - rpm-build

        sudo zypper install dkms make linux-glibc-devel lsb-release rpm-build

# Dependencies

This driver is part of a collection of kernel-mode drivers that enable support for Intel graphics. The backports collection within https://github.com/intel-gpu includes:

- [Intel® Graphics Driver Backports for Linux](https://github.com/intel-gpu/intel-gpu-i915-backports) - The main graphics driver (includes a compatible DRM subsystem and dmabuf if necessary)
- [Intel® Converged Security Engine Backports](https://github.com/intel-gpu/intel-gpu-cse-backports) - Converged Security Engine
- [Intel® Platform Monitoring Technology Backports](https://github.com/intel-gpu/intel-gpu-pmt-backports/) - Intel Platform Telemetry
- [Intel® GPU firmware](https://github.com/intel-gpu/intel-gpu-firmware) - Firmware required by intel GPUs.

Each project is tagged consistently, so when pulling these repos, pull the same tag.

# Dynamic Kernel Module Support(DKMS) based package creation

We need to create dmabuf and i915 dkms packages using the below command.

    make dkmsrpm-pkg

  Above  will create rpm packages at $HOME/rpmbuild/RPMS/x86_64/

# Installation
    sudo rpm -ivh intel-dmabuf-dkms*.rpm intel-i915-dkms*.rpm
    # Reboot the device after installation of all packages.
    sudo reboot
## Installation varification
Please grep **backport**  from dmesg after reboot. you should see something like below

    > sudo dmesg |grep -i backport
    [sudo] password for gta:
    [    4.042298] DMABUF-COMPAT BACKPORTED INIT
    [    4.042374] Loading dma-buf modules backported from DII_5606_prerelease
    [    4.042374] DMA BUF backport generated by backports.git SLES15_SP3_5606_PRERELEASE_220413.0
    [    4.042936] I915 COMPAT BACKPORTED INIT
    [    4.042936] Loading I915 modules backported from DII_5606_prerelease
    [    4.042937] I915 backport generated by backports.git SLES15_SP3_5606_PRERELEASE_220413.0
    [    4.049920] [drm] DRM BACKPORTED INIT
    [    4.323473] [drm] DRM_KMS_HELPER BACKPORTED INIT
    [    4.419171] [drm] I915 BACKPORTED INIT
