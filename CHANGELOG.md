# [Latest] 2.2.0
    - Added support for [snappy](https://google.github.io/snappy/)
    - Fixing examples in README for bzip and gzip 
    - Allowing for empty configuration when using Ananke compression factory 
      - and allowing for not providing a configuration at all 
    
# 2.1.1
    - Fixing spelling mistake `algorithmn` => `algorithm`

# 2.1.0
    - Added factory for zippers 
    - Simple compress and decompress functions 
    - Fixed bug in gzip wrapper
    
# 2.0.0
    - Changed API for gzip 
      - Now compress returns a bool to indicated if compression happened along side the compressed vector
    - Added support for bzip2 
    - Follows the same API as gzip
  
# 1.0.0

Intial release with support for gzip
