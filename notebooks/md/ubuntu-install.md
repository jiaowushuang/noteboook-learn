About ubuntu install
============

Why ubuntu?

    1 Its development is open(GNU-linux)
    2 Downloads and upgrades are free
    3 Its quick to install
    4 upgrades is easy(auto-internet)
    5 support is readily available(volunteers)
    6 enterprise support is priced modestly
    7 you can modify it 
    8 Its portable(you can run it from a CD-ROM or USB thumb drive without installing it)
    9 It comes with office app(compatible with microsoft office)

the parts that make up ubuntu

    ubuntu is a free/open source OS with a strong usability and ease of installation.
    its a fork of the Debian(a linux distribution) project's code base.

    1 Debian 
    desktop and server

    2 GNU 
    both Debian and ubuntu,and most of their parts,are released under the GNU(GPL/LGPL)
    GNU's goal is making a free OS.eg linux kernel. so it stands for GNU not unix;itself released under the GPL.

    3 the linux kernel
    the core OS used by all distribution of linux.

    4 Tux
    as the linux logo
    
    5 linux distribution
    linux comes in a variety of different versions called distributions.
    each distribution consists of the linux kernel along with libraries and utilities from GNU project.
    eg table1-1 some of the most popular linux distributions(you can find you want)

    6 office versions
    ubuntu kubuntu xubuntu mythbuntu netbook-edition

    7 X window system
    graphics display.it's separate from linux and run on many other OS(unix/unix-like) as well.
    it's free and open source like ubuntu.

    8 linux desktop environments
    GNOME KDE Xfce

    10 linux package manager
    there are different managers for different distributions.ubuntu uses the synaptic package manager;or the ubuntu software center.

    11 the ubuntu community
    open source :use and modify(released under the same license).
    http://ubuntu.com/community.

    12 ubuntu versions
    there are two releases of ubuntu each year,generally around 4 and October.
    version num is accronding to.

    13 things you see(graphic)
    things you don't see(OS files,program source code,configuration files,and the like)


*Installing and upgrading ubuntu*

1 live DVD disc / Download and burn ISO disc images.
  
	live DVD disc: if you don't want to install anything,it's ok.because the DVD itself is a fully working installation and will run from the disc without the need to install anything.therefore you can test to ensure it will work properly on your computer before installing it.(电脑必须内置DVD光驱)

	good: run ubuntu without installing anything.once in order,you can choose to install ubuntu.(as the only OS or an additional OS with windows or run without installing)
	bad: slower;OS exists only in RAM, any settings or documents will be lost when you close a session(but have tech to change it).

	first: ensure that your BIOS settings allow booting from your CD/DVD drive.(systems usually do this by default;if not,systems will advice how to change it)
	second:insert the disc into your drive and restart computer.force computer to boot from the DVD(windows:restart+F12 or others).choose language.wait 30 seconds.
  
	the main menu
    five steps:
  
    1 try ubuntu without any change to your computer(during,check whether connect ethernet,mouse,keyboard,monitor,sound card,and other peripherals work)
    2 install ubuntu:install it on your computer
    3 check disc for defects:test whether faulty
    4 test memory:check out your computer's memory is in working order
    5 boot from first hard disk: quit from the DVD when running the OS installed.

	the function key options:
	Before selecting one of the main five menu choices,you can set up various features by these options.
    
	F1 help:
    F2 language:
    F3 keymap:choose your country
    F4 modes:the graphic mode to use(unless you experience problems,you should choose default)
    F5 accessibility: assistive features
    F6 other options:different parameters for booting ubuntu.(for help F1)
    ESC return

  2 Alternative distros(Saved as ISO files)
  
    ISO是CD-ROM的代表,可以轻易的转化。如：可以复制到CD盘;也可以被打开，像传统discs一样（前提安装正确的软件并经过burn）。
    每一个ISO文件都有其MD5 hashes.即使原始ISO文件仅改变一个字节，那其MD5 hashes也不同。WINDOWS:winMD5sum可以检查出ISO文件的MD5值。
    
    1 如何安装a distribution? 使用虚拟环境（virtualBox）或是burn them to CD/DVD discs,and perform a full installation.
    2 如何下载a distribution? 使用ISO镜像文件（除DVD外的方法）注意不同distribution的使用范围;并且在你安装ubuntu desktop后，可以添加其他的distributions，在你登录时需要选择某个的distribution。

    1 Burn a CD or DVD
    WINDOWSneed:Active ISO Burner(ISO->CD/DVD) if you intend to use the Wubi installer,you must burn the ISO file to CD.

    Burn to a USB thumb drive
    When the utility’s window opens, select the ISO image as the source and the USB device for the destination, and then click Make Startup Disk.

    You can then use the USB drive as if it were a Live CD, by inserting it into a target computer that is configured so it is able to boot from such a device. 
    This is the perfect way to try out Ubuntu or install it on a laptop without an optical drive. You can also use the USB drive as a handy, portable Ubuntu environment that lets you boot up on
    any computer that you are allowed to access.

    2 Virtual Installation
    You can create virtual hard drives and CD-ROM drives, as well as specify the amount of RAM to provide, among various other configuration options.
    Microsoft Virtual PC;VMware;Sun VirtualBox;others

    3 full installation
        1. As the sole operating system, taking over all hard disk partitions
        2. As part of a dual- or multi-boot setup with its own hard disk partition(the most efficient way to run ubuntu together with windows)(but take a long time).
        3. Using the Wubi program to run Ubuntu from within a Microsoft Windows virtual disk, without any hard disk repartitioning(offer the fastest Installation)
        Note:Wubi also changes your boot menu options, adding Ubuntu as an alternative operating system that you can select with the cursor keys and Enter at boot time(同option2)

Installing Ubuntu Under Windows(option3)

    Wubi is a powerful program that creates a virtual hard disk under Windows and runs Ubuntu from there as part of a dual- or multi-boot operating system.
        1 Performing the installation(remove the DVD from the drive)
            • wubi.exe(ubuntu will be displayed as a selectable OS alongside your usual Windows OS)
            • ubuntu-9.10-desktop-i386.iso(others)
        2 Important considerations
            1 There appears to be a bug in the Wubi program-click the Continue button several times until the program starts.
            2 If you burn the ISO file to CD-you can insert it into a Windows CD-ROM drive and Wubi will offer the option to install Ubuntu inside Windows without you having to copy an ISO file to your computer—but this only works with CDs
            3 If Wubi detects any problems with the disc, it may try to download the ISO over the Internet. If this happens, it is usually because the ISO you copied to the desktop is corrupted.
            4 causes a slight performance hit
    
Installing Ubuntu As a Standalone OS

    need:perform some partitioning of your hard disk during the installation process.
        live DVD
        If your computer doesn’t already have an operating system.Auto.
        If there is already an operating system on the disk,you now have to decide whether to install the operating systems side by side(双系统-Sharing the hard disk) or overwrite the original operating system（单系统-备份-Using the entire hard disk);
        AND...If you have decided to add Ubuntu alongside your previous operating system(双系统)，需要决定ubuntu和windows之间的磁盘容量。
        Entering your user details   
        After rebooting
            1 If you have installed Ubuntu as the computer’s only operating system;Auto.
            2 Dual- and multi-boot setups:you will be offered a choice each time your computer boots up,which could include Windows and OS X, as well as the recovery mode and memtest86+.
        Recovery mode:The recovery mode entries boot the associated Ubuntu operating system into a command mode from which you can perform various repair functions.
        Memory testing:when you suspect you may have a problem with your computer’s system memory.ESC-RETURN.


Upgrading to New Releases

    1 Installing from CD
    2 Upgrading an Existing Installation

Summary

	Ubuntu is generally very fast to install, unless you make it part of a dual- or multi-boot setup and therefore have to resize partitions. And even then it’s a lot quicker to install Ubuntu than some other major operating systems.











