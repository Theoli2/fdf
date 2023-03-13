/*
** mlx_new_image.c for MiniLibX in raytraceur
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Aug 14 15:29:14 2000 Charlie Root
** Last update Wed May 25 16:46:31 2011 Olivier Crouzet
*/




#include	"mlx_int.h"

/*
** To handle X errors
*/

#define	X_ShmAttach	1

int	mlx_X_error;

int	shm_att_pb(Display *d,XErrorEvent *ev)
{
  if (ev->request_code==146 && ev->minor_code==X_ShmAttach)
    write(2,WARN_SHM_ATTACH,strlen(WARN_SHM_ATTACH));
  mlx_X_error = 1;
}


/*
**  Data malloc :  height+32 ( bitmap_pad=32 ),    *4 = *32 / 8bit
*/


void	*mlx_int_new_xshm_image(t_xvar *xvar,int height,int width,int format)
{
  t_img	*img;
  int	(*save_handler)();

  if (!(img = malloc(sizeof(*img))))
    return ((void *)0);
  bzero(img,sizeof(*img));
  img->data = 0;
  img->image = XShmCreateImage(xvar->display,xvar->visual,xvar->depth,
			       format,img->data,&(img->shm),height,width);
  if (!img->image)
    {
      free(img);
      return ((void *)0);
    }
  img->height = height;
  img->width = width;
  img->size_line = img->image->bytes_per_line;
  img->bpp = img->image->bits_per_pixel;
  img->format = format;
  img->shm.shmid = shmget(IPC_PRIVATE,(height+32)*width*4,IPC_CREAT|0777);
  if (img->shm.shmid==-1)
    {
      XDestroyImage(img->image);
      free(img);
      return ((void *)0);
    }
  img->data = img->shm.shmaddr = img->image->data = shmat(img->shm.shmid,0,0);
  if (img->data==(void *)-1)
    {
      shmctl(img->shm.shmid,IPC_RMID,0);
      XDestroyImage(img->image);
      free(img);
      return ((void *)0);
    }
  img->shm.readOnly = False;
  mlx_X_error = 0;
  save_handler = XSetErrorHandler(shm_att_pb);
  if (!XShmAttach(xvar->display,&(img->shm)) ||
      0&XSync(xvar->display,False) || mlx_X_error)
    {
      XSetErrorHandler(save_handler);
      shmdt(img->data);
      shmctl(img->shm.shmid,IPC_RMID,0);
      XDestroyImage(img->image);
      free(img);
      return ((void *)0);
    }
  XSetErrorHandler(save_handler);
  shmctl(img->shm.shmid,IPC_RMID,0);
  if (xvar->pshm_format==format)
    {
      img->pix = XShmCreatePixmap(xvar->display,xvar->root,img->shm.shmaddr,
				  &(img->shm),height,width,xvar->depth);
      img->type = MLX_TYPE_SHM_PIXMAP;
    }
  else
    {
      img->pix = XCreatePixmap(xvar->display,xvar->root,
			       height,width,xvar->depth);
      img->type = MLX_TYPE_SHM;
    }
  if (xvar->do_flush)
    XFlush(xvar->display);
  return (img);
}



void	*mlx_int_new_image(t_xvar *xvar,int height, int width,int format)
{
  t_img	*img;

  if (!(img = malloc(sizeof(*img))))
    return ((void *)0);
  if (!(img->data = malloc((height+32)*width*4)))
  {
    free(img);
    return ((void *)0);
  }
  bzero(img->data,(height+32)*width*4);
  img->image = XCreateImage(xvar->display,xvar->visual,xvar->depth,format,0,
			    img->data,height,width,32,0);
  if (!img->image)
    {
      free(img->data);
      free(img);
      return ((void *)0);
    }
  img->gc = 0;
  img->size_line = img->image->bytes_per_line;
  img->bpp = img->image->bits_per_pixel;
  img->height = height;
  img->width = width;
  img->pix = XCreatePixmap(xvar->display,xvar->root,height,width,xvar->depth);
  img->format = format;
  img->type = MLX_TYPE_XIMAGE;
  if (xvar->do_flush)
    XFlush(xvar->display);
  return (img);
}


void	*mlx_new_image(t_xvar *xvar,int height, int width)
{
  t_img	*img;

  if (xvar->use_xshm)
    if (img = mlx_int_new_xshm_image(xvar,height,width,ZPixmap))
      return (img);
  return (mlx_int_new_image(xvar,height,width,ZPixmap));
}

void	*mlx_new_image2(t_xvar *xvar,int height, int width)
{
  t_img	*img;

  if (xvar->use_xshm)
    if (img = mlx_int_new_xshm_image(xvar,height,width,XYPixmap))
      return (img);
  return (mlx_int_new_image(xvar,height,width,XYPixmap));
}
