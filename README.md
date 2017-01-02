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
`mstream` uses an unorthodox methodology of creation & allocation of memory via templates. Creating a new instance of `mstream` will take two input arguments `<size, alignment>` instead of taking the arguments through the constructor. `alloc()` does the same thing, except that `alloc()` has "optional template arguments," that will by default pull the class' template inputs if the arguments are not specified.

```C++
/*
    Example
*/
// Constructs a new stream with a length of `16` and a byte alingment of `1`.
mstream<16, 1> my_stream;

// This will alocate new memory using the class' input args: <16, 1>
my_stream.alloc<>();

// This will allocate new memory given user-defined input args.
my_stream.alloc<32, 4>();
```
