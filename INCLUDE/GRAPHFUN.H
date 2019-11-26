//@ author Shubham Jain
#ifdef GRAPH_H
void Graphics::fillrect(int x,int y,int w,int h,long color)
{if(w<0){w*=-1;x=x-w+1;}
 if(h<0){h*=-1;y=y-h+1;}
 if(x<0){w=w+x;x=0;}
 if(y<0){h=h+y;y=0;}
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768){h=768-y;}
 int b1=y>>4,b2=(y+h-1)>>4;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++)
   for(int j=0;j<w;j++)
    *(vmem+i*1024+x+j)=color;
 }
 else
 { for(int i=(y%16);i<16;i++)
    for(int j=0;j<w;j++)
     *(vmem+i*1024+x+j)=color;
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++)
     for(j=0;j<w;j++)
      *(vmem+i*1024+x+j)=color;
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++)
    for(j=0;j<w;j++)
     *(vmem+i*1024+x+j)=color;
 }
}
void Graphics::fillrect(int x,int y,int w,int h,Image &im)
{if(w<0){w*=-1;x=x-w+1;}
 if(h<0){h*=-1;y=y-h+1;}
 if(x<0){w=w+x;x=0;}
 if(y<0){h=h+y;y=0;}
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768){h=768-y;}
 int b1=y>>4,b2=(y+h-1)>>4,c=0;
 BYTE4 color;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++,c++)
   for(int j=0;j<w;j++)
   {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
   }
 }
 else
 { for(int i=(y%16);i<16;i++,c++)
    for(int j=0;j<w;j++)
    {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++,c++)
     for(j=0;j<w;j++)
     {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
     }
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++,c++)
    for(j=0;j<w;j++)
    {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
 }
}

void Graphics::drawImage(Image &im,int x,int y,int w,int h,int x1,int y1)
{if(w<0||h<0||x1<0||y1<0||x1>=im.w||y1>=im.h||x>=1024||y>=768)return;
 if((x1+w)>im.w)w=im.w-x1;
 if((y1+h)>im.h)h=im.h-y1;
 if(x<0){x1-=x;w+=x;x=0;}
 if(y<0){y1-=y;h+=y;y=0;}
 if(x1>=im.w||y1>=im.h)return;
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768 ){h=768 -y;}
 int b1=y>>4,b2=(y+h-1)>>4,c=0;
 BYTE4 color;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++,c++)
   for(int j=0;j<w;j++)
   {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
   }
 }
 else
 { for(int i=(y%16);i<16;i++,c++)
    for(int j=0;j<w;j++)
    {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++,c++)
     for(j=0;j<w;j++)
     {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
     }
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++,c++)
    for(j=0;j<w;j++)
    {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
 }
}
Image Graphics::getImage(int x,int y,int w,int h)
{Image im(0,0,0);
 if(w<0){w*=-1;x=x-w+1;}
 if(h<0){h*=-1;y=y-h+1;}
 if(x<0){w=w+x;x=0;}
 if(y<0){h=h+y;y=0;}
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768){h=768-y;}
 long *l=new long[w*h];
 if(l==0){return im;}
 im.ptr=l;im.w=w;im.h=h;
 int b1=y>>4,b2=(y+h-1)>>4,c=0;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++,c++)
   for(int j=0;j<w;j++)
    *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
 }
 else
 { for(int i=(y%16);i<16;i++,c++)
    for(int j=0;j<w;j++)
     *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++,c++)
     for(j=0;j<w;j++)
     *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++,c++)
    for(j=0;j<w;j++)
    *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
 }
 return im;
}
#endif