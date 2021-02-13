#include "partition.h"

void SetPartition(struct VDIFile *f, struct PartitionEntry pentry)
{
    VDISeek(f, 446, 64);
    ssize_t read = VDIRead(f, pentry.partitionEntries, 64);
    try
    {
        if(read < 0)
            throw read;
        //   read valid
    }
    catch (ssize_t read)
    {
        std::cout << "invalid read in SetPartition";
    }
    /*
        perror('FillPartition');*/
}


struct PartitionFile *PartitionOpen(struct VDIFile *f, struct PartitionEntry pentry)
{
    SetPartition(f, pentry);
    int partitionnumber;
    struct PartitionFile *p = new PartitionFile;
    /*switch(partitionnumber)
    {
    	case pentry.partitionEntries[0][4]==0x83:
    	partitionnumber = 0;
    	break;
    	case pentry.partitionEntries[1][4]==0x83:
    	partitionnumber=1;
    	break;
    	case pentry.partitionEntries[2][4]==0x83:
    	partitionnumber=2;
    	break;
    	case pentry.partitionEntries[3][4]==0x83:
    	partitionnumber=3;
    	break;
    	default:
    	std::cout<<"invalid value in PartitionOpen, pentry.partitionEntries not found";
    	break;

    	}*/
    if(pentry.partitionEntries[0][4] == 0x83)
        partitionnumber = 0;
    else if(pentry.partitionEntries[1][4] == 0x83)
        partitionnumber = 1;
    else if(pentry.partitionEntries[2][4] == 0x83)
        partitionnumber = 2;
    else if(pentry.partitionEntries[3][4] == 0x83)
        partitionnumber = 3;
    else
        return nullptr;

    p->pstart = pentry.partitionEntries[partitionnumber][8] | pentry.partitionEntries[partitionnumber][9] << 8 |
                pentry.partitionEntries[partitionnumber][10] << 16 | pentry.partitionEntries[partitionnumber][11] << 24;
    p->pstart = p->pstart * 512;
    p->psize = pentry.partitionEntries[partitionnumber][12] | pentry.partitionEntries[partitionnumber][13] << 8 |
               pentry.partitionEntries[partitionnumber][14] << 16 | pentry.partitionEntries[partitionnumber][14] << 24;
    p->psize = p->psize * 512;
    p->vdi = f;


    return p;

}
void PartitionClose(struct PartitionFile *p)
{
    close(p->vdi->fd);
    delete p;
}
ssize_t PartitionRead(struct VDIFile *f, void *buf, size_t count, struct PartitionFile *p)
{
    if(count <= p->psize)
    {
        ssize_t read = VDIRead(f, buf, count);
        return read;
    }
    else
        return -1;
}
ssize_t PartitionWrite(struct VDIFile *f, void *buf, size_t count, struct PartitionFile *p)
{
    if(count <= p->psize)
    {
        ssize_t write = VDIRead(f, buf, count);
        return write;
    }
    else
        return -1;
}
off_t PartitionSeek(struct PartitionFile *p, off_t offset, int anchor, struct VDIFile *f)
{
    uint8_t newpos;
    off_t location;

    if(anchor == SEEK_SET)
        newpos = offset;
    else if(anchor == SEEK_CUR)
        newpos += offset;
    else if(anchor == SEEK_END)
        newpos = offset + f->header.cbDisk;
    else
        newpos = f->cursor;
    if(newpos >= 0 && newpos <= f->header.cbDisk && newpos <= p->psize)
        f->cursor = newpos;
    return f->cursor;
}


