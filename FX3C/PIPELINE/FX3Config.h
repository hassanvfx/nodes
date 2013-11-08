

// configuration constants


// OS constants

#define FX3_OS_ANDROID	0
#define FX3_OS_IOS		1
#define FX3_OS_MAC 		0

#define IS_IOS      (defined(FX3_OS_IOS) && FX3_OS_IOS ==1)
#define IS_MAC      (defined(FX3_OS_MAC) && FX3_OS_MAC ==1)
#define IS_ANDROID  (defined(FX3_OS_ANDROID) && FX3_OS_ANDROID ==1)

//#define USE_RENDER_MSAA         0

// provider (reader) and writer constants

#define FX3_PROVIDER_FFMPEG 	1	
#define FX3_PROVIDER_JELLYBEAN	0
#define FX3_PROVIDER_RAWVIDEO 	0

#define FX3_WRITER_FFMPEG 		1	
#define FX3_WRITER_X264			0
#define FX3_WRITER_JELLYBEAN	0
#define FX3_WRITER_RAWVIDEO 	0
