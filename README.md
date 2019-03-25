awsv4-cpp
=========

A c++11 implementation of awsv4 signature version 4 signing process  (an extension of already built solution)

For more information on this process, please see 

    http://docs.aws.amazon.com/general/latest/gr/signature-version-4.html

This library will send request and display response from aws endpoint.

This library uses `openssl`, `Poco` , `libcurlpp`, `curl` and `boost`.

in ubuntu , we can use the following packages. dependencies may change. so tune accordingly.

poco : libpoco-dev: C++ Portable Components (POCO) Development files

Tune the `Makefile` as you see fit.

The `main2.cpp` is a basic test suite that uses the sample data available at 

    http://docs.aws.amazon.com/general/latest/gr/sigv4_signing.html

add your access and secret access key on the go in main2.cpp.
