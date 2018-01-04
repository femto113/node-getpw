# getpw [![Build Status](https://secure.travis-ci.org/femto113/node-getpw.png)](http://travis-ci.org/femto113/node-getpw)

node.js wrapper for POSIX {getpwuid()} function.  The main use of this method
is to convert numeric user ids (e.g. as obtainable from {process.getuid()})
into string user names.

For more info

    man getpwuid

## Install

    npm install getpw

or

    git clone http://github.com/femto113/node-getpw.git
    cd getpw
    npm link

## Example

    var getpw = require("getpw");

    console.log(getpw.getpwuid(process.getuid())
    
outputs something like

  {
    pw_name: 'femto113',
    pw_uid: 113,
    pw_gid: 22,
    pw_dir: '/home/femto113',
    pw_shell: '/bin/tcsh'
  }

## TODO

- will probably blow up on non-POSIX (i.e. Windows) OS 
- there are some other functions (esp. {getpwnam()}) that 
  would make sense to add

## Changes

* 1.0.0 - updated to use node-gyp and modern V8 API
