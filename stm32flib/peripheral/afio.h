#ifndef __AFIO_H__
#define __AFIO_H__

#ifdef __cplusplus
extern "C" {
#endif

int AFIO_Enable(void);
int AFIO_Disable(void);
int AFIO_IsEnabled(void);

#ifdef __cplusplus
}
#endif

#endif // __AFIO_H__
