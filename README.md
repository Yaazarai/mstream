# mstream
A basic memory stream with byte alignment.

```C++
// Template for deifning the size and alignment of the mstream (memory-stream) upon construction.
template<size_t size, size_t align>
class mstream {
    public:
    //Constructs a new mstream and allocates it's memory.
    mstream();
    // Destructs the mstream freeing up all memory.
    ~mstream();
    // Aligns a position--e.g. seek position--to the byte alignment of the mstream.
    void inline fast_align(size_t& iter);
    // Allows you to cast the mstream straight to it's raw buffer.
    operator byte*();
    // Whether or not the mstream is holding allocated memory.
    bool memexists();
    // Returns the length of the mstream in bytes.
    size_t length();
    // Seek to an ** aligned ** position in the mstream.
    void seek(size_t pos);
    // Get the current ** aligned ** seek position.
    size_t get_seek();
    // Zeros out all memory in the array.
    void memzero();
    // Deallocates the mstream's memory--not the actual mstream.
    void dealloc();
    // Allocates new memory for the mstream with the new size and alignment.
    template<size_t new_size, size_t new_align>
    void alloc();
    // Reads a value type <T> from the mstream.
    template<typename T>
    T read()
    // Reads a value type <T> from the mstream at the indictaed seek position (does not move the seek mstream's position).
    template<typename T>
    T peek(size_t seek)
    // Writes a value tpye <T> to the mstream.
    template<typename T>
    void write(T value);
    // Writes a value type <T> to the mstream at the indictaed seek position (does not move the seek mstream's position).
    template<typename T>
    void poke(T value, size_t seek);
};
```
