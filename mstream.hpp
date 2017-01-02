#ifndef MSTREAM
#define MSTREAM
    #include "byte.hpp"
    #include <string.h>

    template<size_t size, size_t align>
    class mstream {
        private:
        byte* memory = nullptr;
        size_t seek_in = 0,
            size_of,
            align_of = 0,
            fast_al = 0,
            fast_nt = 0;

        public:
        mstream() {
            memory = new byte[size]();
            size_of = size;
            align_of = align;
            fast_al = align - 1;
            fast_nt = ~(align - 1);
        };

        ~mstream() {
            if (memory == nullptr)
                delete[] memory;
        }

        void inline fast_align(size_t& iter) { iter = (iter + fast_al) & fast_nt; };
        
        operator byte*() { return memory; };

        bool memexists() { return memory != nullptr; }

        size_t length() { return size_of; };

        void seek(size_t pos) { fast_align(seek_in = pos); };

        size_t get_seek() { return seek_in; };

        void memzero() { for(int i = 0; i < size_of; i++) memory[i] = 0; }

        void dealloc() {
            delete[] memory;
            size_of = 0;
            align_of = 0;
        }

        template<size_t new_size = size, size_t new_align = align>
        void alloc() {
            size_of = new_size;
            align_of = new_align;
            fast_al = align - 1;
            fast_nt = ~(align - 1);
            memory = new byte[size_of];
        }

        template<typename T>
        T read() {
            int offset = seek_in;
            seek_in = seek_in + sizeof(T);
            fast_align(seek_in);
            return *reinterpret_cast<T*>(memory + offset);
        };

        template<typename T>
        T peek(size_t seek) {
            int seek_old = seek_in;
            seek_in = seek;
            fast_align(seek_in);
            T val = *reinterpret_cast<T*>(memory + offset);
            seek_in = seek_old;
            return val;
        };

        template<typename T>
        void write(T value) {
            T* data = reinterpret_cast<T*>(memory + seek_in);
            seek_in = seek_in + sizeof(T);
            fast_align(seek_in);
            *data = value;
        };

        template<typename T>
        void poke(T value, size_t seek) {
            int seek_old = seek_in;
            seek_in = seek;
            fast_align(seek_in);
            write(value);
            seek_in = seek_old;

        }
    };
#endif
