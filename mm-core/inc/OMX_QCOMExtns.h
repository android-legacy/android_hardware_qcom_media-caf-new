/*--------------------------------------------------------------------------
Copyright (c) 2009-2014, The Linux Foundation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of The Linux Foundation nor
      the names of its contributors may be used to endorse or promote
      products derived from this software without specific prior written
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------------*/
#ifndef __OMX_QCOM_EXTENSIONS_H__
#define __OMX_QCOM_EXTENSIONS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*============================================================================
*//** @file OMX_QCOMExtns.h
  This header contains constants and type definitions that specify the
  extensions added to the OpenMAX Vendor specific APIs.

*//*========================================================================*/


///////////////////////////////////////////////////////////////////////////////
//                             Include Files
///////////////////////////////////////////////////////////////////////////////
#include "OMX_Core.h"
#include "OMX_Video.h"

/**
 * This extension is used to register mapping of a virtual
 * address to a physical address. This extension is a parameter
 * which can be set using the OMX_SetParameter macro. The data
 * pointer corresponding to this extension is
 * OMX_QCOM_MemMapEntry. This parameter is a 'write only'
 * parameter (Current value cannot be queried using
 * OMX_GetParameter macro).
 */
#define OMX_QCOM_EXTN_REGISTER_MMAP     "OMX.QCOM.index.param.register_mmap"

/**
 * This structure describes the data pointer corresponding to
 * the OMX_QCOM_MMAP_REGISTER_EXTN extension. This parameter
 * must be set only 'after' populating a port with a buffer
 * using OMX_UseBuffer, wherein the data pointer of the buffer
 * corresponds to the virtual address as specified in this
 * structure.
 */
struct OMX_QCOM_PARAM_MEMMAPENTRYTYPE
{
    OMX_U32 nSize;              /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /**< OMX specification version information */
    OMX_U32 nPortIndex;         /**< Port number the structure applies to */

    /**
     * The virtual address of memory block
     */
    OMX_U64 nVirtualAddress;

    /**
     * The physical address corresponding to the virtual address. The physical
     * address is contiguous for the entire valid range of the virtual
     * address.
     */
    OMX_U64 nPhysicalAddress;
};

#define QOMX_VIDEO_IntraRefreshRandom (OMX_VIDEO_IntraRefreshVendorStartUnused + 0)

/* This error event is used for H.264 long-term reference (LTR) encoding.
 * When IL client specifies an LTR frame with its identifier via
 * OMX_QCOM_INDEX_CONFIG_VIDEO_LTRUSE to the encoder, if the specified
 * LTR frame can not be located by the encoder in its LTR list, the encoder
 * issues this error event to IL client to notify the failure of LTRUse config.
 */
#define QOMX_ErrorLTRUseFailed        (OMX_ErrorVendorStartUnused + 1)

#define QOMX_VIDEO_BUFFERFLAG_BFRAME 0x00100000

#define QOMX_VIDEO_BUFFERFLAG_EOSEQ  0x00200000

#define QOMX_VIDEO_BUFFERFLAG_MBAFF  0x00400000

#define OMX_QCOM_PORTDEFN_EXTN   "OMX.QCOM.index.param.portdefn"
/* Allowed APIs on the above Index: OMX_GetParameter() and OMX_SetParameter() */

typedef enum OMX_QCOMMemoryRegion
{
    OMX_QCOM_MemRegionInvalid,
    OMX_QCOM_MemRegionEBI1,
    OMX_QCOM_MemRegionSMI,
    OMX_QCOM_MemRegionMax = 0X7FFFFFFF
} OMX_QCOMMemoryRegion;

typedef enum OMX_QCOMCacheAttr
{
    OMX_QCOM_CacheAttrNone,
    OMX_QCOM_CacheAttrWriteBack,
    OMX_QCOM_CacheAttrWriteThrough,
    OMX_QCOM_CacheAttrMAX = 0X7FFFFFFF
} OMX_QCOMCacheAttr;

typedef struct OMX_QCOMRectangle
{
   OMX_S32 x;
   OMX_S32 y;
   OMX_S32 dx;
   OMX_S32 dy;
} OMX_QCOMRectangle;

/** OMX_QCOMFramePackingFormat
  * Input or output buffer format
  */
typedef enum OMX_QCOMFramePackingFormat
{
  /* 0 - unspecified
   */
  OMX_QCOM_FramePacking_Unspecified,

  /*  1 - Partial frames may be present OMX IL 1.1.1 Figure 2-10:
   *  Case 1??Each Buffer Filled In Whole or In Part
   */
  OMX_QCOM_FramePacking_Arbitrary,

  /*  2 - Multiple complete frames per buffer (integer number)
   *  OMX IL 1.1.1 Figure 2-11: Case 2�Each Buffer Filled with
   *  Only Complete Frames of Data
   */
  OMX_QCOM_FramePacking_CompleteFrames,

  /*  3 - Only one complete frame per buffer, no partial frame
   *  OMX IL 1.1.1 Figure 2-12: Case 3�Each Buffer Filled with
   *  Only One Frame of Compressed Data. Usually at least one
   *  complete unit of data will be delivered in a buffer for
   *  uncompressed data formats.
   */
  OMX_QCOM_FramePacking_OnlyOneCompleteFrame,

  /*  4 - Only one complete subframe per buffer, no partial subframe
   *  Example: In H264, one complete NAL per buffer, where one frame
   *  can contatin multiple NAL
   */
  OMX_QCOM_FramePacking_OnlyOneCompleteSubFrame,

  OMX_QCOM_FramePacking_MAX = 0X7FFFFFFF
} OMX_QCOMFramePackingFormat;

typedef struct OMX_QCOM_PARAM_PORTDEFINITIONTYPE {
 OMX_U32 nSize;           /** Size of the structure in bytes */
 OMX_VERSIONTYPE nVersion;/** OMX specification version information */
 OMX_U32 nPortIndex;    /** Portindex which is extended by this structure */

 /** Platform specific memory region EBI1, SMI, etc.,*/
 OMX_QCOMMemoryRegion nMemRegion;

 OMX_QCOMCacheAttr nCacheAttr; /** Cache attributes */

 /** Input or output buffer format */
 OMX_U32 nFramePackingFormat;

} OMX_QCOM_PARAM_PORTDEFINITIONTYPE;

typedef struct OMX_QCOM_VIDEO_PARAM_QPRANGETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 minQP;
    OMX_U32 maxQP;
} OMX_QCOM_VIDEO_PARAM_QPRANGETYPE;

#define OMX_QCOM_PLATFORMPVT_EXTN   "OMX.QCOM.index.param.platformprivate"
/** Allowed APIs on the above Index: OMX_SetParameter() */

typedef enum OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE
{
    /** Enum for PMEM information */
    OMX_QCOM_PLATFORM_PRIVATE_PMEM = 0x1
} OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE;

/** IL client will set the following structure. A failure
 *  code will be returned if component does not support the
 *  value provided for 'type'.
 */
struct OMX_QCOM_PLATFORMPRIVATE_EXTN
{
    OMX_U32 nSize;        /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /** OMX spec version information */
    OMX_U32 nPortIndex;  /** Port number on which usebuffer extn is applied */

    /** Type of extensions should match an entry from
     OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE
    */
    OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE type;
};

typedef struct OMX_QCOM_PLATFORM_PRIVATE_PMEM_INFO
{
    /** pmem file descriptor */
    OMX_U32 pmem_fd;
    /** Offset from pmem device base address */
    OMX_U32 offset;
    OMX_U32 size;
    OMX_U32 mapped_size;
    OMX_PTR buffer;
}OMX_QCOM_PLATFORM_PRIVATE_PMEM_INFO;

typedef struct OMX_QCOM_PLATFORM_PRIVATE_ENTRY
{
    /** Entry type */
    OMX_QCOM_PLATFORM_PRIVATE_ENTRY_TYPE type;

    /** Pointer to platform specific entry */
    void* entry;
}OMX_QCOM_PLATFORM_PRIVATE_ENTRY;

typedef struct OMX_QCOM_PLATFORM_PRIVATE_LIST
{
    /** Number of entries */
    OMX_U32 nEntries;

    /** Pointer to array of platform specific entries *
     * Contiguous block of OMX_QCOM_PLATFORM_PRIVATE_ENTRY element
    */
    OMX_QCOM_PLATFORM_PRIVATE_ENTRY* entryList;
}OMX_QCOM_PLATFORM_PRIVATE_LIST;

#define OMX_QCOM_FRAME_PACKING_FORMAT   "OMX.QCOM.index.param.framepackfmt"
/* Allowed API call: OMX_GetParameter() */
/* IL client can use this index to rerieve the list of frame formats *
 * supported by the component */

typedef struct OMX_QCOM_FRAME_PACKINGFORMAT_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nIndex;
    OMX_QCOMFramePackingFormat eframePackingFormat;
} OMX_QCOM_FRAME_PACKINGFORMAT_TYPE;


/**
 * Following is the enum for color formats supported on Qualcomm
 * MSMs YVU420SemiPlanar color format is not defined in OpenMAX
 * 1.1.1 and prior versions of OpenMAX specification.
 */

enum OMX_QCOM_COLOR_FORMATTYPE
{

/** YVU420SemiPlanar: YVU planar format, organized with a first
 *  plane containing Y pixels, and a second plane containing
 *  interleaved V and U pixels. V and U pixels are sub-sampled
 *  by a factor of two both horizontally and vertically.
 */
    QOMX_COLOR_FormatYVU420SemiPlanar = 0x7FA30C00,
    QOMX_COLOR_FormatYVU420PackedSemiPlanar32m4ka,
    QOMX_COLOR_FormatYUV420PackedSemiPlanar16m2ka,
    QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka,
    QOMX_COLOR_FORMATYUV420PackedSemiPlanar32m,
    QOMX_COLOR_FormatAndroidOpaque = (OMX_COLOR_FORMATTYPE) OMX_COLOR_FormatVendorStartUnused  + 0x789,
};

enum OMX_QCOM_VIDEO_CODINGTYPE
{
/** Codecs support by qualcomm which are not listed in OMX 1.1.x
 *  spec
 *   */
    OMX_QCOM_VIDEO_CodingVC1  = 0x7FA30C00 ,
    OMX_QCOM_VIDEO_CodingWMV9 = 0x7FA30C01,
    QOMX_VIDEO_CodingDivx = 0x7FA30C02,     /**< Value when coding is Divx */
    QOMX_VIDEO_CodingSpark = 0x7FA30C03,     /**< Value when coding is Sorenson Spark */
    QOMX_VIDEO_CodingVp = 0x7FA30C04,
    QOMX_VIDEO_CodingVp8 = 0x7FA30C05,
    QOMX_VIDEO_CodingHevc = 0x7FA30C06
};

enum OMX_QCOM_EXTN_INDEXTYPE
{
    /** Qcom proprietary extension index list */

    /* "OMX.QCOM.index.param.register_mmap" */
    OMX_QcomIndexRegmmap = 0x7F000000,

    /* "OMX.QCOM.index.param.platformprivate" */
    OMX_QcomIndexPlatformPvt = 0x7F000001,

    /* "OMX.QCOM.index.param.portdefn" */
    OMX_QcomIndexPortDefn = 0x7F000002,

    /* "OMX.QCOM.index.param.framepackingformat" */
    OMX_QcomIndexPortFramePackFmt = 0x7F000003,

    /*"OMX.QCOM.index.param.Interlaced */
    OMX_QcomIndexParamInterlaced = 0x7F000004,

    /*"OMX.QCOM.index.config.interlaceformat */
    OMX_QcomIndexConfigInterlaced = 0x7F000005,

    /*"OMX.QCOM.index.param.syntaxhdr" */
    QOMX_IndexParamVideoSyntaxHdr = 0x7F000006,

    /*"OMX.QCOM.index.config.intraperiod" */
    QOMX_IndexConfigVideoIntraperiod = 0x7F000007,

    /*"OMX.QCOM.index.config.randomIntrarefresh" */
    QOMX_IndexConfigVideoIntraRefresh = 0x7F000008,

    /*"OMX.QCOM.index.config.video.TemporalSpatialTradeOff" */
    QOMX_IndexConfigVideoTemporalSpatialTradeOff = 0x7F000009,

    /*"OMX.QCOM.index.param.video.EncoderMode" */
    QOMX_IndexParamVideoEncoderMode = 0x7F00000A,

    /*"OMX.QCOM.index.param.Divxtype */
    OMX_QcomIndexParamVideoDivx = 0x7F00000B,

    /*"OMX.QCOM.index.param.Sparktype */
    OMX_QcomIndexParamVideoSpark = 0x7F00000C,

    /*"OMX.QCOM.index.param.Vptype */
    OMX_QcomIndexParamVideoVp = 0x7F00000D,

    OMX_QcomIndexQueryNumberOfVideoDecInstance = 0x7F00000E,

    OMX_QcomIndexParamVideoSyncFrameDecodingMode = 0x7F00000F,

    OMX_QcomIndexParamVideoDecoderPictureOrder = 0x7F000010,

    /* "OMX.QCOM.index.config.video.FramePackingInfo" */
    OMX_QcomIndexConfigVideoFramePackingArrangement = 0x7F000011,

    OMX_QcomIndexParamConcealMBMapExtraData = 0x7F000012,

    OMX_QcomIndexParamFrameInfoExtraData = 0x7F000013,

    OMX_QcomIndexParamInterlaceExtraData = 0x7F000014,

    OMX_QcomIndexParamH264TimeInfo = 0x7F000015,

    OMX_QcomIndexParamIndexExtraDataType = 0x7F000016,

    OMX_GoogleAndroidIndexEnableAndroidNativeBuffers = 0x7F000017,

    OMX_GoogleAndroidIndexUseAndroidNativeBuffer = 0x7F000018,

    OMX_GoogleAndroidIndexGetAndroidNativeBufferUsage = 0x7F000019,

    /*"OMX.QCOM.index.config.video.QPRange" */
    OMX_QcomIndexConfigVideoQPRange = 0x7F00001A,

    /*"OMX.QCOM.index.param.EnableTimeStampReoder"*/
    OMX_QcomIndexParamEnableTimeStampReorder = 0x7F00001B,

    /*"OMX.google.android.index.storeMetaDataInBuffers"*/
    OMX_QcomIndexParamVideoMetaBufferMode = 0x7F00001C,

    /*"OMX.google.android.index.useAndroidNativeBuffer2"*/
    OMX_GoogleAndroidIndexUseAndroidNativeBuffer2 = 0x7F00001D,

    /*"OMX.QCOM.index.param.VideoMaxAllowedBitrateCheck"*/
    OMX_QcomIndexParamVideoMaxAllowedBitrateCheck = 0x7F00001E,

    OMX_QcomIndexEnableSliceDeliveryMode = 0x7F00001F,

    OMX_QcomIndexEnableExtnUserData = 0x7F000020,

    /*"OMX.QCOM.index.param.video.EnableSmoothStreaming"*/
    OMX_QcomIndexParamEnableSmoothStreaming = 0x7F000021,

    /*"OMX.QCOM.index.param.video.QPRange" */
    OMX_QcomIndexParamVideoQPRange = 0x7F000022,

    OMX_QcomIndexEnableH263PlusPType = 0x7F000023,

    /*"OMX.QCOM.index.param.video.LTRCountRangeSupported"*/
    QOMX_IndexParamVideoLTRCountRangeSupported = 0x7F000024,

    /*"OMX.QCOM.index.param.video.LTRMode"*/
    QOMX_IndexParamVideoLTRMode = 0x7F000025,

    /*"OMX.QCOM.index.param.video.LTRCount"*/
    QOMX_IndexParamVideoLTRCount = 0x7F000026,

    /*"OMX.QCOM.index.config.video.LTRPeriod"*/
    QOMX_IndexConfigVideoLTRPeriod = 0x7F000027,

    /*"OMX.QCOM.index.config.video.LTRUse"*/
    QOMX_IndexConfigVideoLTRUse = 0x7F000028,

    /*"OMX.QCOM.index.config.video.LTRMark"*/
    QOMX_IndexConfigVideoLTRMark = 0x7F000029,

    /* OMX.google.android.index.prependSPSPPSToIDRFrames */
    OMX_QcomIndexParamSequenceHeaderWithIDR = 0x7F00002A,

    OMX_QcomIndexParamH264AUDelimiter = 0x7F00002B,

    OMX_QcomIndexParamVideoDownScalar = 0x7F00002C,

    /* "OMX.QCOM.index.param.video.FramePackingExtradata" */
    OMX_QcomIndexParamVideoFramePackingExtradata = 0x7F00002D,

    /* google smooth-streaming support */
    OMX_QcomIndexParamVideoAdaptivePlaybackMode = 0x7F00002E,

    /* "OMX.QCOM.index.param.video.QPExtradata" */
    OMX_QcomIndexParamVideoQPExtraData = 0x7F00002F,

    /* "OMX.QCOM.index.param.video.InputBitsInfoExtradata" */
    OMX_QcomIndexParamVideoInputBitsInfoExtraData = 0x7F000030,

    /* VP8 Hierarchical P support */
    OMX_QcomIndexHierarchicalStructure = 0x7F000031,

    /*"OMX.QCOM.index.param.video.LTRCount"*/
    OMX_QcomIndexParamVideoLTRCount = QOMX_IndexParamVideoLTRCount,

    /*"OMX.QCOM.index.config.video.LTRUse"*/
    OMX_QcomIndexConfigVideoLTRUse = QOMX_IndexConfigVideoLTRUse,

    /*"OMX.QCOM.index.config.video.LTRMark"*/
    OMX_QcomIndexConfigVideoLTRMark = QOMX_IndexConfigVideoLTRMark,

    OMX_QcomIndexParamPerfLevel = 0x7F000032,

    OMX_QcomIndexParamH264VUITimingInfo = 0x7F000033,

    OMX_QcomIndexParamPeakBitrate = 0x7F000034,

    /* Enable InitialQP index */
    QOMX_IndexParamVideoInitialQp = 0x7F00003B,

    OMX_QcomIndexParamSetMVSearchrange = 0x7F00003C,
};
 
/**
 * Initial QP parameter.  This structure is used to enable
 * vendor specific extension to let client enable setting
 * initial QP values to I P B Frames
 *
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  OMX_U32 nQpI       : First Iframe QP
 *  OMX_U32 nQpP       : First Pframe QP
 *  OMX_U32 nQpB       : First Bframe QP
 *  OMX_U32 bEnableInitQp : Bit field indicating which frame type(s) shall
 *                             use the specified initial QP.
 *                          Bit 0: Enable initial QP for I/IDR
 *                                 and use value specified in nInitQpI
 *                          Bit 1: Enable initial QP for P
 *                                 and use value specified in nInitQpP
 *                          Bit 2: Enable initial QP for B
 *                                 and use value specified in nInitQpB
 */

typedef struct QOMX_EXTNINDEX_VIDEO_INITIALQP {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nQpI;
    OMX_U32 nQpP;
    OMX_U32 nQpB;
    OMX_U32 bEnableInitQp;
} QOMX_EXTNINDEX_VIDEO_INITIALQP;

/**
 * Extension index parameter.  This structure is used to enable
 * vendor specific extension on input/output port and
 * to pass the required flags and data, if any.
 * The format of flags and data being passed is known to
 * the client and component apriori.
 *
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure plus pData size
 *  nVersion           : OMX specification version information
 *  nPortIndex         : Indicates which port to set
 *  bEnable            : Extension index enable (1) or disable (0)
 *  nFlags             : Extension index flags, if any
 *  nDataSize          : Size of the extension index data to follow
 *  pData              : Extension index data, if present.
 */
typedef struct QOMX_EXTNINDEX_PARAMTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_U32 nFlags;
    OMX_U32 nDataSize;
    OMX_PTR pData;
} QOMX_EXTNINDEX_PARAMTYPE;

/**
 * Range index parameter.  This structure is used to enable
 * vendor specific extension on input/output port and
 * to pass the required minimum and maximum values
 *
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  nMin               : Minimum value
 *  nMax               : Maximum value
 *  nSteSize           : Step size
 */
typedef struct QOMX_EXTNINDEX_RANGETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_S32 nMin;
    OMX_S32 nMax;
    OMX_S32 nStepSize;
} QOMX_EXTNINDEX_RANGETYPE;

/**
 *   Specifies LTR mode types.
 */
typedef enum QOMX_VIDEO_LTRMODETYPE
{
    QOMX_VIDEO_LTRMode_Disable    = 0x0, /**< LTR encoding is disabled */
    QOMX_VIDEO_LTRMode_Manual     = 0x1, /**< In this mode, IL client configures
                                           **  the encoder the LTR count and manually
                                           **  controls the marking and use of LTR
                                           **  frames during video encoding.
                                           */
    QOMX_VIDEO_LTRMode_Auto       = 0x2, /**< In this mode, IL client configures
                                           **  the encoder the LTR count and LTR
                                           **  period. The encoder marks LTR frames
                                           **  automatically based on the LTR period
                                           **  during video encoding. IL client controls
                                           **  the use of LTR frames.
                                           */
    QOMX_VIDEO_LTRMode_MAX    = 0x7FFFFFFF /** Maximum LTR Mode type */
} QOMX_VIDEO_LTRMODETYPE;

/**
 * LTR mode index parameter.  This structure is used
 * to enable vendor specific extension on output port
 * to pass the LTR mode information.
 *
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  eLTRMode           : Specifies the LTR mode used in encoder
 */
typedef struct QOMX_VIDEO_PARAM_LTRMODE_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_VIDEO_LTRMODETYPE eLTRMode;
} QOMX_VIDEO_PARAM_LTRMODE_TYPE;

/**
 * LTR count index parameter.  This structure is used
 * to enable vendor specific extension on output port
 * to pass the LTR count information.
 *
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  nCount             : Specifies the number of LTR frames stored in the
 *                       encoder component
 */
typedef struct QOMX_VIDEO_PARAM_LTRCOUNT_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nCount;
} QOMX_VIDEO_PARAM_LTRCOUNT_TYPE;


/**
 * This should be used with OMX_QcomIndexParamVideoLTRCount extension.
 */
typedef QOMX_VIDEO_PARAM_LTRCOUNT_TYPE OMX_QCOM_VIDEO_PARAM_LTRCOUNT_TYPE;

/**
 * LTR period index parameter.  This structure is used
 * to enable vendor specific extension on output port
 * to pass the LTR period information.
 *
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  nFrames            : Specifies the number of frames between two consecutive
 *                       LTR frames.
 */
typedef struct QOMX_VIDEO_CONFIG_LTRPERIOD_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nFrames;
} QOMX_VIDEO_CONFIG_LTRPERIOD_TYPE;

/**
 * Marks the next encoded frame as an LTR frame.
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  nID                : Specifies the identifier of the LTR frame to be marked
 *                       as reference frame for encoding subsequent frames.
 */
typedef struct QOMX_VIDEO_CONFIG_LTRMARK_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nID;
} QOMX_VIDEO_CONFIG_LTRMARK_TYPE;

/**
 * This should be used with OMX_QcomIndexConfigVideoLTRMark extension.
 */
typedef QOMX_VIDEO_CONFIG_LTRMARK_TYPE OMX_QCOM_VIDEO_CONFIG_LTRMARK_TYPE;

/**
 * Specifies an LTR frame to encode subsequent frames.
 * STRUCT MEMBERS:
 *  nSize              : Size of Structure in bytes
 *  nVersion           : OpenMAX IL specification version information
 *  nPortIndex         : Index of the port to which this structure applies
 *  nID                : Specifies the identifier of the LTR frame to be used
                         as reference frame for encoding subsequent frames.
 *  nFrames            : Specifies the number of subsequent frames to be
                         encoded using the LTR frame with its identifier
                         nID as reference frame. Short-term reference frames
                         will be used thereafter. The value of 0xFFFFFFFF
                         indicates that all subsequent frames will be
                         encodedusing this LTR frame as reference frame.
 */
typedef struct QOMX_VIDEO_CONFIG_LTRUSE_TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nID;
    OMX_U32 nFrames;
} QOMX_VIDEO_CONFIG_LTRUSE_TYPE;

/**
 * This should be used with OMX_QcomIndexConfigVideoLTRUse extension.
 */
typedef QOMX_VIDEO_CONFIG_LTRUSE_TYPE OMX_QCOM_VIDEO_CONFIG_LTRUSE_TYPE;

/**
 * Enumeration used to define the video encoder modes
 *
 * ENUMS:
 *  EncoderModeDefault : Default video recording mode.
 *                       All encoder settings made through
 *                       OMX_SetParameter/OMX_SetConfig are applied. No
 *                       parameter is overridden.
 *  EncoderModeMMS : Video recording mode for MMS (Multimedia Messaging
 *                   Service). This mode is similar to EncoderModeDefault
 *                   except that here the Rate control mode is overridden
 *                   internally and set as a variant of variable bitrate with
 *                   variable frame rate. After this mode is set if the IL
 *                   client tries to set OMX_VIDEO_CONTROLRATETYPE via
 *                   OMX_IndexParamVideoBitrate that would be rejected. For
 *                   this, client should set mode back to EncoderModeDefault
 *                   first and then change OMX_VIDEO_CONTROLRATETYPE.
 */
typedef enum QOMX_VIDEO_ENCODERMODETYPE
{
    QOMX_VIDEO_EncoderModeDefault        = 0x00,
    QOMX_VIDEO_EncoderModeMMS            = 0x01,
    QOMX_VIDEO_EncoderModeMax            = 0x7FFFFFFF
} QOMX_VIDEO_ENCODERMODETYPE;

/**
 * This structure is used to set the video encoder mode.
 *
 * STRUCT MEMBERS:
 *  nSize      : Size of the structure in bytes
 *  nVersion   : OMX specification version info
 *  nPortIndex : Port that this structure applies to
 *  nMode : defines the video encoder mode
 */
typedef struct QOMX_VIDEO_PARAM_ENCODERMODETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_VIDEO_ENCODERMODETYPE nMode;
} QOMX_VIDEO_PARAM_ENCODERMODETYPE;

/**
 * This structure describes the parameters corresponding to the
 * QOMX_VIDEO_SYNTAXHDRTYPE extension. This parameter can be queried
 * during the loaded state.
 */

typedef struct QOMX_VIDEO_SYNTAXHDRTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nBytes;          /** The number of bytes filled in to the buffer */
   OMX_U8 data[1];          /** Buffer to store the header information */
} QOMX_VIDEO_SYNTAXHDRTYPE;

/**
 * This structure describes the parameters corresponding to the
 * QOMX_VIDEO_TEMPORALSPATIALTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid.  This is primarily
 * used for setting MaxQP from the application.  This is set on the out port.
 */

typedef struct QOMX_VIDEO_TEMPORALSPATIALTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nTSFactor;       /** Temoral spatial tradeoff factor value in 0-100 */
} QOMX_VIDEO_TEMPORALSPATIALTYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_INTRAPERIODTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid.  This is set on the out port.
 */

typedef struct QOMX_VIDEO_INTRAPERIODTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nIDRPeriod;      /** This specifies coding a frame as IDR after every nPFrames
                                of intra frames. If this parameter is set to 0, only the
                                first frame of the encode session is an IDR frame. This
                                field is ignored for non-AVC codecs and is used only for
                                codecs that support IDR Period */
   OMX_U32 nPFrames;         /** The number of "P" frames between two "I" frames */
   OMX_U32 nBFrames;         /** The number of "B" frames between two "I" frames */
} QOMX_VIDEO_INTRAPERIODTYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_ULBUFFEROCCUPANCYTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is used for the buffer negotiation
 * with other clients.  This is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_ULBUFFEROCCUPANCYTYPE
{
   OMX_U32 nSize;            /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion; /** OMX specification version information */
   OMX_U32 nPortIndex;       /** Portindex which is extended by this structure */
   OMX_U32 nBufferOccupancy; /** The number of bytes to be set for the buffer occupancy */
} OMX_QCOM_VIDEO_CONFIG_ULBUFFEROCCUPANCYTYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_RANDOMINTRAREFRESHTYPE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is primarily used for the dynamic/random
 * intrarefresh.  This is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_RANDOMINTRAREFRESHTYPE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nRirMBs;         /** The number of MBs to be set for intrarefresh */
} OMX_QCOM_VIDEO_CONFIG_RANDOMINTRAREFRESHTYPE;


/**
 * This structure describes the parameters corresponding to the
 * OMX_QCOM_VIDEO_CONFIG_QPRANGE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is primarily
 * used for the min/max QP to be set from the application.  This
 * is set on the out port.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_QPRANGE
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nMinQP;          /** The number for minimum quantization parameter */
   OMX_U32 nMaxQP;          /** The number for maximum quantization parameter */
} OMX_QCOM_VIDEO_CONFIG_QPRANGE;

/**
 * This structure describes the parameters for the
 * OMX_QcomIndexParamH264AUDelimiter extension.  It enables/disables
 * the AU delimiters in the H264 stream, which is used by WFD.
 */
typedef struct OMX_QCOM_VIDEO_CONFIG_H264_AUD
{
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_BOOL bEnable;        /** Enable/disable the setting */
} OMX_QCOM_VIDEO_CONFIG_H264_AUD;

typedef enum QOMX_VIDEO_PERF_LEVEL
{
    OMX_QCOM_PerfLevelNominal,
    OMX_QCOM_PerfLevelTurbo
} QOMX_VIDEO_PERF_LEVEL;

/**
 * This structure describes the parameters corresponding
 * to OMX_QcomIndexParamPerfLevel extension. It will set
 * the performance mode specified as QOMX_VIDEO_PERF_LEVEL.
 */
typedef struct OMX_QCOM_VIDEO_PARAM_PERF_LEVEL {
    OMX_U32 nSize;                      /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;           /** OMX specification version information */
    QOMX_VIDEO_PERF_LEVEL ePerfLevel;   /** Performance level */
} OMX_QCOM_VIDEO_PARAM_PERF_LEVEL;

/**
 * This structure describes the parameters corresponding
 * to OMX_QcomIndexParamH264VUITimingInfo extension. It
 * will enable/disable the VUI timing info.
 */
typedef struct OMX_QCOM_VIDEO_PARAM_VUI_TIMING_INFO {
    OMX_U32 nSize;              /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /** OMX specification version information */
    OMX_BOOL bEnable;           /** Enable/disable the setting */
} OMX_QCOM_VIDEO_PARAM_VUI_TIMING_INFO;

/**
 * This structure describes the parameters corresponding
 * to OMX_QcomIndexParamPeakBitrate extension. It will
 * set the peak bitrate specified by nPeakBitrate.
 */
typedef struct OMX_QCOM_VIDEO_PARAM_PEAK_BITRATE {
    OMX_U32 nSize;              /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /** OMX specification version information */
    OMX_U32 nPeakBitrate;       /** Peak bitrate value */
} OMX_QCOM_VIDEO_PARAM_PEAK_BITRATE;

typedef struct OMX_VENDOR_EXTRADATATYPE  {
    OMX_U32 nPortIndex;
    OMX_U32 nDataSize;
    OMX_U8  *pData;     // cdata (codec_data/extradata)
} OMX_VENDOR_EXTRADATATYPE;

/**
 * This structure describes the parameters corresponding to the
 * OMX_VENDOR_VIDEOFRAMERATE extension. This parameter can be set
 * dynamically during any state except the state invalid. This is
 * used for frame rate to be set from the application. This
 * is set on the in port.
 */
typedef struct OMX_VENDOR_VIDEOFRAMERATE  {
   OMX_U32 nSize;           /** Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion;/** OMX specification version information */
   OMX_U32 nPortIndex;      /** Portindex which is extended by this structure */
   OMX_U32 nFps;            /** Frame rate value */
   OMX_BOOL bEnabled;       /** Flag to enable or disable client's frame rate value */
} OMX_VENDOR_VIDEOFRAMERATE;

typedef enum OMX_INDEXVENDORTYPE {
    OMX_IndexVendorFileReadInputFilename = 0xFF000001,
    OMX_IndexVendorParser3gpInputFilename = 0xFF000002,
    OMX_IndexVendorVideoExtraData = 0xFF000003,
    OMX_IndexVendorAudioExtraData = 0xFF000004,
    OMX_IndexVendorVideoFrameRate = 0xFF000005,
} OMX_INDEXVENDORTYPE;

typedef enum OMX_QCOM_VC1RESOLUTIONTYPE
{
   OMX_QCOM_VC1_PICTURE_RES_1x1,
   OMX_QCOM_VC1_PICTURE_RES_2x1,
   OMX_QCOM_VC1_PICTURE_RES_1x2,
   OMX_QCOM_VC1_PICTURE_RES_2x2
} OMX_QCOM_VC1RESOLUTIONTYPE;

typedef enum OMX_QCOM_INTERLACETYPE
{
    OMX_QCOM_InterlaceFrameProgressive,
    OMX_QCOM_InterlaceInterleaveFrameTopFieldFirst,
    OMX_QCOM_InterlaceInterleaveFrameBottomFieldFirst,
    OMX_QCOM_InterlaceFrameTopFieldFirst,
    OMX_QCOM_InterlaceFrameBottomFieldFirst,
    OMX_QCOM_InterlaceFieldTop,
    OMX_QCOM_InterlaceFieldBottom
}OMX_QCOM_INTERLACETYPE;

typedef struct OMX_QCOM_PARAM_VIDEO_INTERLACETYPE
{
    OMX_U32 nSize;           /** Size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;/** OMX specification version information */
    OMX_U32 nPortIndex;    /** Portindex which is extended by this structure */
    OMX_BOOL bInterlace;  /** Interlace content **/
}OMX_QCOM_PARAM_VIDEO_INTERLACETYPE;

typedef struct OMX_QCOM_CONFIG_INTERLACETYPE
{
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nIndex;
    OMX_QCOM_INTERLACETYPE eInterlaceType;
}OMX_QCOM_CONFIG_INTERLACETYPE;

#define MAX_PAN_SCAN_WINDOWS 4

typedef struct OMX_QCOM_PANSCAN
{
   OMX_U32 numWindows;
   OMX_QCOMRectangle window[MAX_PAN_SCAN_WINDOWS];
} OMX_QCOM_PANSCAN;

typedef struct OMX_QCOM_ASPECT_RATIO
{
   OMX_U32 aspectRatioX;
   OMX_U32 aspectRatioY;
} OMX_QCOM_ASPECT_RATIO;

typedef struct OMX_QCOM_DISPLAY_ASPECT_RATIO
{
   OMX_U32 displayVerticalSize;
   OMX_U32 displayHorizontalSize;
} OMX_QCOM_DISPLAY_ASPECT_RATIO;

typedef struct OMX_QCOM_FRAME_PACK_ARRANGEMENT
{
  OMX_U32 nSize;
  OMX_VERSIONTYPE nVersion;
  OMX_U32 nPortIndex;
  OMX_U32 id;
  OMX_U32 cancel_flag;
  OMX_U32 type;
  OMX_U32 quincunx_sampling_flag;
  OMX_U32 content_interpretation_type;
  OMX_U32 spatial_flipping_flag;
  OMX_U32 frame0_flipped_flag;
  OMX_U32 field_views_flag;
  OMX_U32 current_frame_is_frame0_flag;
  OMX_U32 frame0_self_contained_flag;
  OMX_U32 frame1_self_contained_flag;
  OMX_U32 frame0_grid_position_x;
  OMX_U32 frame0_grid_position_y;
  OMX_U32 frame1_grid_position_x;
  OMX_U32 frame1_grid_position_y;
  OMX_U32 reserved_byte;
  OMX_U32 repetition_period;
  OMX_U32 extension_flag;
} OMX_QCOM_FRAME_PACK_ARRANGEMENT;

typedef struct OMX_QCOM_EXTRADATA_QP
{
   OMX_U32        nQP;
} OMX_QCOM_EXTRADATA_QP;

typedef struct OMX_QCOM_EXTRADATA_BITS_INFO
{
   OMX_U32 header_bits;
   OMX_U32 frame_bits;
} OMX_QCOM_EXTRADATA_BITS_INFO;

typedef struct OMX_QCOM_EXTRADATA_FRAMEINFO
{
   // common frame meta data. interlace related info removed
   OMX_VIDEO_PICTURETYPE  ePicType;
   OMX_QCOM_INTERLACETYPE interlaceType;
   OMX_QCOM_PANSCAN       panScan;
   OMX_QCOM_ASPECT_RATIO  aspectRatio;
   OMX_QCOM_DISPLAY_ASPECT_RATIO displayAspectRatio;
   OMX_U32                nConcealedMacroblocks;
   OMX_U32                nFrameRate;
   OMX_TICKS              nTimeStamp;
} OMX_QCOM_EXTRADATA_FRAMEINFO;

typedef struct OMX_QCOM_EXTRADATA_FRAMEDIMENSION
{
   /** Frame Dimensions added to each YUV buffer */
   OMX_U32   nDecWidth;  /** Width  rounded to multiple of 16 */
   OMX_U32   nDecHeight; /** Height rounded to multiple of 16 */
   OMX_U32   nActualWidth; /** Actual Frame Width */
   OMX_U32   nActualHeight; /** Actual Frame Height */

} OMX_QCOM_EXTRADATA_FRAMEDIMENSION;

typedef struct OMX_QCOM_H264EXTRADATA
{
   OMX_U64 seiTimeStamp;
} OMX_QCOM_H264EXTRADATA;

typedef struct OMX_QCOM_VC1EXTRADATA
{
   OMX_U32                     nVC1RangeY;
   OMX_U32                     nVC1RangeUV;
   OMX_QCOM_VC1RESOLUTIONTYPE eVC1PicResolution;
} OMX_QCOM_VC1EXTRADATA;

typedef union OMX_QCOM_EXTRADATA_CODEC_DATA
{
   OMX_QCOM_H264EXTRADATA h264ExtraData;
   OMX_QCOM_VC1EXTRADATA vc1ExtraData;
} OMX_QCOM_EXTRADATA_CODEC_DATA;

typedef struct OMX_QCOM_EXTRADATA_MBINFO
{
   OMX_U32 nFormat;
   OMX_U32 nDataSize;
   OMX_U8  data[0];
} OMX_QCOM_EXTRADATA_MBINFO;

typedef enum OMX_QCOM_EXTRADATATYPE
{
    OMX_ExtraDataFrameInfo =               0x7F000001,
    OMX_ExtraDataH264 =                    0x7F000002,
    OMX_ExtraDataVC1 =                     0x7F000003,
    OMX_ExtraDataFrameDimension =          0x7F000004,
    OMX_ExtraDataVideoEncoderSliceInfo =   0x7F000005,
    OMX_ExtraDataConcealMB =               0x7F000006,
    OMX_ExtraDataInterlaceFormat =         0x7F000007,
    OMX_ExtraDataPortDef =                 0x7F000008,
    OMX_ExtraDataMP2ExtnData =             0x7F000009,
    OMX_ExtraDataMP2UserData =             0x7F00000a,
    OMX_ExtraDataVideoLTRInfo =            0x7F00000b,
    OMX_ExtraDataFramePackingArrangement = 0x7F00000c,
    OMX_ExtraDataQP =                      0x7F00000d,
    OMX_ExtraDataInputBitsInfo =           0x7F00000e,
    OMX_ExtraDataVideoEncoderMBInfo =      0x7F00000f,
} OMX_QCOM_EXTRADATATYPE;

typedef struct  OMX_STREAMINTERLACEFORMATTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bInterlaceFormat;
    OMX_U32 nInterlaceFormats;
} OMX_STREAMINTERLACEFORMAT;

typedef enum OMX_INTERLACETYPE
{
   OMX_InterlaceFrameProgressive,
   OMX_InterlaceInterleaveFrameTopFieldFirst,
   OMX_InterlaceInterleaveFrameBottomFieldFirst,
   OMX_InterlaceFrameTopFieldFirst,
   OMX_InterlaceFrameBottomFieldFirst
} OMX_INTERLACES;


#define OMX_EXTRADATA_HEADER_SIZE 20

/**
 * AVC profile types, each profile indicates support for various
 * performance bounds and different annexes.
 */
typedef enum QOMX_VIDEO_AVCPROFILETYPE {
    QOMX_VIDEO_AVCProfileBaseline      = OMX_VIDEO_AVCProfileBaseline,
    QOMX_VIDEO_AVCProfileMain          = OMX_VIDEO_AVCProfileMain,
    QOMX_VIDEO_AVCProfileExtended      = OMX_VIDEO_AVCProfileExtended,
    QOMX_VIDEO_AVCProfileHigh          = OMX_VIDEO_AVCProfileHigh,
    QOMX_VIDEO_AVCProfileHigh10        = OMX_VIDEO_AVCProfileHigh10,
    QOMX_VIDEO_AVCProfileHigh422       = OMX_VIDEO_AVCProfileHigh422,
    QOMX_VIDEO_AVCProfileHigh444       = OMX_VIDEO_AVCProfileHigh444,
    /* QCom specific profile indexes */
    QOMX_VIDEO_AVCProfileConstrainedBaseline   = OMX_VIDEO_AVCProfileVendorStartUnused + 1,
} QOMX_VIDEO_AVCPROFILETYPE;

/**
 * DivX Versions
 */
typedef enum  QOMX_VIDEO_DIVXFORMATTYPE {
    QOMX_VIDEO_DIVXFormatUnused = 0x01, /**< Format unused or unknown */
    QOMX_VIDEO_DIVXFormat311    = 0x02, /**< DivX 3.11 */
    QOMX_VIDEO_DIVXFormat4      = 0x04, /**< DivX 4 */
    QOMX_VIDEO_DIVXFormat5      = 0x08, /**< DivX 5 */
    QOMX_VIDEO_DIVXFormat6      = 0x10, /**< DivX 6 */
    QOMX_VIDEO_DIVXFormatKhronosExtensions = 0x6F000000,
    QOMX_VIDEO_DIVXFormatVendorStartUnused = 0x7F000000,
    QOMX_VIDEO_DIVXFormatMax = 0x7FFFFFFF
} QOMX_VIDEO_DIVXFORMATTYPE;

/**
 * DivX profile types, each profile indicates support for
 * various performance bounds.
 */
typedef enum QOMX_VIDEO_DIVXPROFILETYPE {
    QOMX_VIDEO_DivXProfileqMobile = 0x01, /**< qMobile Profile */
    QOMX_VIDEO_DivXProfileMobile  = 0x02, /**< Mobile Profile */
    QOMX_VIDEO_DivXProfileMT      = 0x04, /**< Mobile Theatre Profile */
    QOMX_VIDEO_DivXProfileHT      = 0x08, /**< Home Theatre Profile */
    QOMX_VIDEO_DivXProfileHD      = 0x10, /**< High Definition Profile */
    QOMX_VIDEO_DIVXProfileKhronosExtensions = 0x6F000000,
    QOMX_VIDEO_DIVXProfileVendorStartUnused = 0x7F000000,
    QOMX_VIDEO_DIVXProfileMax = 0x7FFFFFFF
} QOMX_VIDEO_DIVXPROFILETYPE;

/**
 * DivX Video Params
 *
 *  STRUCT MEMBERS:
 *  nSize      : Size of the structure in bytes
 *  nVersion   : OMX specification version information
 *  nPortIndex : Port that this structure applies to
 *  eFormat    : Version of DivX stream / data
 *  eProfile   : Profile of DivX stream / data
 */
typedef struct QOMX_VIDEO_PARAM_DIVXTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_VIDEO_DIVXFORMATTYPE eFormat;
    QOMX_VIDEO_DIVXPROFILETYPE eProfile;
} QOMX_VIDEO_PARAM_DIVXTYPE;



/**
 *  VP Versions
 */
typedef enum QOMX_VIDEO_VPFORMATTYPE {
    QOMX_VIDEO_VPFormatUnused = 0x01, /**< Format unused or unknown */
    QOMX_VIDEO_VPFormat6      = 0x02, /**< VP6 Video Format */
    QOMX_VIDEO_VPFormat7      = 0x04, /**< VP7 Video Format */
    QOMX_VIDEO_VPFormat8      = 0x08, /**< VP8 Video Format */
    QOMX_VIDEO_VPFormatKhronosExtensions = 0x6F000000,
    QOMX_VIDEO_VPFormatVendorStartUnused = 0x7F000000,
    QOMX_VIDEO_VPFormatMax = 0x7FFFFFFF
} QOMX_VIDEO_VPFORMATTYPE;

/**
 * VP profile types, each profile indicates support for various
 * encoding tools.
 */
typedef enum QOMX_VIDEO_VPPROFILETYPE {
    QOMX_VIDEO_VPProfileSimple   = 0x01, /**< Simple Profile, applies to VP6 only */
    QOMX_VIDEO_VPProfileAdvanced = 0x02, /**< Advanced Profile, applies to VP6 only */
    QOMX_VIDEO_VPProfileVersion0 = 0x04, /**< Version 0, applies to VP7 and VP8 */
    QOMX_VIDEO_VPProfileVersion1 = 0x08, /**< Version 1, applies to VP7 and VP8 */
    QOMX_VIDEO_VPProfileVersion2 = 0x10, /**< Version 2, applies to VP8 only */
    QOMX_VIDEO_VPProfileVersion3 = 0x20, /**< Version 3, applies to VP8 only */
    QOMX_VIDEO_VPProfileKhronosExtensions = 0x6F000000,
    QOMX_VIDEO_VPProfileVendorStartUnused = 0x7F000000,
    QOMX_VIDEO_VPProfileMax = 0x7FFFFFFF
} QOMX_VIDEO_VPPROFILETYPE;

/**
 * VP Video Params
 *
 *  STRUCT MEMBERS:
 *  nSize      : Size of the structure in bytes
 *  nVersion   : OMX specification version information
 *  nPortIndex : Port that this structure applies to
 *  eFormat    : Format of VP stream / data
 *  eProfile   : Profile or Version of VP stream / data
 */
typedef struct QOMX_VIDEO_PARAM_VPTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_VIDEO_VPFORMATTYPE eFormat;
    QOMX_VIDEO_VPPROFILETYPE eProfile;
} QOMX_VIDEO_PARAM_VPTYPE;

/**
 * Spark Versions
 */
typedef enum QOMX_VIDEO_SPARKFORMATTYPE {
    QOMX_VIDEO_SparkFormatUnused = 0x01, /**< Format unused or unknown */
    QOMX_VIDEO_SparkFormat0      = 0x02, /**< Video Format Version 0 */
    QOMX_VIDEO_SparkFormat1      = 0x04, /**< Video Format Version 1 */
    QOMX_VIDEO_SparkFormatKhronosExtensions = 0x6F000000,
    QOMX_VIDEO_SparkFormatVendorStartUnused = 0x7F000000,
    QOMX_VIDEO_SparkFormatMax = 0x7FFFFFFF
} QOMX_VIDEO_SPARKFORMATTYPE;

/**
 * Spark Video Params
 *
 *  STRUCT MEMBERS:
 *  nSize      : Size of the structure in bytes
 *  nVersion   : OMX specification version information
 *  nPortIndex : Port that this structure applies to
 *  eFormat    : Version of Spark stream / data
 */
typedef struct QOMX_VIDEO_PARAM_SPARKTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_VIDEO_SPARKFORMATTYPE eFormat;
} QOMX_VIDEO_PARAM_SPARKTYPE;


typedef struct QOMX_VIDEO_QUERY_DECODER_INSTANCES {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nNumOfInstances;
} QOMX_VIDEO_QUERY_DECODER_INSTANCES;

typedef struct QOMX_ENABLETYPE {
    OMX_BOOL bEnable;
} QOMX_ENABLETYPE;

typedef enum QOMX_VIDEO_EVENTS {
    OMX_EventIndexsettingChanged = OMX_EventVendorStartUnused
} QOMX_VIDEO_EVENTS;

typedef enum QOMX_VIDEO_PICTURE_ORDER {
    QOMX_VIDEO_DISPLAY_ORDER = 0x1,
    QOMX_VIDEO_DECODE_ORDER = 0x2
} QOMX_VIDEO_PICTURE_ORDER;

typedef struct QOMX_VIDEO_DECODER_PICTURE_ORDER {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    QOMX_VIDEO_PICTURE_ORDER eOutputPictureOrder;
} QOMX_VIDEO_DECODER_PICTURE_ORDER;

typedef struct QOMX_INDEXEXTRADATATYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnabled;
    OMX_INDEXTYPE nIndex;
} QOMX_INDEXEXTRADATATYPE;

typedef struct QOMX_INDEXTIMESTAMPREORDER {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
} QOMX_INDEXTIMESTAMPREORDER;

typedef struct QOMX_INDEXDOWNSCALAR {
        OMX_U32 nSize;
        OMX_VERSIONTYPE nVersion;
        OMX_U32 nPortIndex;
        OMX_BOOL bEnable;
} QOMX_INDEXDOWNSCALAR;


#define OMX_QCOM_INDEX_PARAM_VIDEO_SYNCFRAMEDECODINGMODE "OMX.QCOM.index.param.video.SyncFrameDecodingMode"
#define OMX_QCOM_INDEX_PARAM_INDEXEXTRADATA "OMX.QCOM.index.param.IndexExtraData"
#define OMX_QCOM_INDEX_PARAM_VIDEO_SLICEDELIVERYMODE "OMX.QCOM.index.param.SliceDeliveryMode"
#define OMX_QCOM_INDEX_PARAM_VIDEO_FRAMEPACKING_EXTRADATA "OMX.QCOM.index.param.video.FramePackingExtradata"
#define OMX_QCOM_INDEX_PARAM_VIDEO_QP_EXTRADATA "OMX.QCOM.index.param.video.QPExtradata"
#define OMX_QCOM_INDEX_PARAM_VIDEO_INPUTBITSINFO_EXTRADATA "OMX.QCOM.index.param.video.InputBitsInfoExtradata"
#define OMX_QCOM_INDEX_CONFIG_VIDEO_FRAMEPACKING_INFO "OMX.QCOM.index.config.video.FramePackingInfo"

typedef enum {
    QOMX_VIDEO_FRAME_PACKING_CHECKERBOARD = 0,
    QOMX_VIDEO_FRAME_PACKING_COLUMN_INTERLEAVE = 1,
    QOMX_VIDEO_FRAME_PACKING_ROW_INTERLEAVE = 2,
    QOMX_VIDEO_FRAME_PACKING_SIDE_BY_SIDE = 3,
    QOMX_VIDEO_FRAME_PACKING_TOP_BOTTOM = 4,
    QOMX_VIDEO_FRAME_PACKING_TEMPORAL = 5,
} QOMX_VIDEO_FRAME_PACKING_ARRANGEMENT;

typedef enum {
    QOMX_VIDEO_CONTENT_UNSPECIFIED = 0,
    QOMX_VIDEO_CONTENT_LR_VIEW = 1,
    QOMX_VIDEO_CONTENT_RL_VIEW = 2,
} QOMX_VIDEO_CONTENT_INTERPRETATION;

/**
 * Specifies the extended picture types. These values should be
 * OR'd along with the types defined in OMX_VIDEO_PICTURETYPE to
 * signal all pictures types which are allowed.
 *
 * ENUMS:
 *  H.264 Specific Picture Types:   IDR
 */
typedef enum QOMX_VIDEO_PICTURETYPE {
    QOMX_VIDEO_PictureTypeIDR = OMX_VIDEO_PictureTypeVendorStartUnused + 0x1000
} QOMX_VIDEO_PICTURETYPE;

typedef enum QOMX_VIDEO_HIERARCHICALCODINGTYPE {
    QOMX_HIERARCHICALCODING_P = 0x01,
    QOMX_HIERARCHICALCODING_B = 0x02,
} QOMX_VIDEO_HIERARCHICALCODINGTYPE;

typedef struct QOMX_VIDEO_HIERARCHICALLAYERS {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nNumLayers;
    QOMX_VIDEO_HIERARCHICALCODINGTYPE eHierarchicalCodingType;
} QOMX_VIDEO_HIERARCHICALLAYERS;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OMX_QCOM_EXTENSIONS_H__ */
