extern unsigned int _start_heap;
#define NULL (((void *)0))

#ifdef OWN_MALLOC

struct malloc_block {
    unsigned int signature;
    unsigned int size;
};

#define SIGNATURE_IN_USE (0xAAC0FFEE)
#define SIGNATURE_FREED  (0xFEEDFACE)

void *malloc(unsigned int size) {

    static unsigned int *end_heap = 0; // static - следит за концом кучи
    struct malloc_block *blk;
    char *ret = NULL;

    if(!end_heap) {
        end_heap = &_start_heap;
    }

    /* Выравнивание по 4 байта. Если число не кратно 4, то дополняем его до ближайшего кратного */
    if (((size >> 2) << 2) != size) {
        size = ((size >> 2) + 1) << 2;
    }

    blk = (struct malloc_block*)&_start_heap;
    /* Сначала ищем высвобожденные и подходящие по размеру блоки */
    while ((unsigned int*)blk < end_heap) {
        if ((blk->signature == SIGNATURE_FREED) && (blk->size >= size)) {
            blk->signature = SIGNATURE_IN_USE;
            ret = ((char*)blk) + sizeof(struct malloc_block);
            return ret;
        }

        blk = ((char*)blk) + sizeof(struct malloc_block) + blk->size;
    }

    /* Если не нашли, выделяем блок нужного размера в конце кучи */
    blk = (struct malloc_block*)end_heap;
    blk->signature = SIGNATURE_IN_USE;
    blk->size = size;
    ret = ((char*)end_heap) + sizeof(struct malloc_block);
    end_heap = (unsigned int*)(ret + size);
    return ret;
}

void free(void *ptr) {
    if(!ptr)
        return;
    struct malloc_block *blk = (struct malloc_block*)
            (((char*)ptr)-sizeof(struct malloc_block));
    if(blk->signature != SIGNATURE_IN_USE)
        return;
    blk->signature = SIGNATURE_FREED;
}

#endif
