cmake_minimum_required (VERSION 2.6)

set(OPENCV_FOLDER E:/githome/opencv/opencv3)
set(OPENCV_EXTRA_MODULE_FOLDER E:/githome/opencv/opencv_contrib3/modules)

set(OPENCV_LIB opencv_aruco345d.lib
	opencv_bgsegm345d.lib
	opencv_bioinspired345d.lib
	opencv_calib3d345d.lib
	opencv_ccalib345d.lib
	opencv_core345d.lib
	opencv_datasets345d.lib
	opencv_dnn_objdetect345d.lib
	opencv_dnn345d.lib
	opencv_dpm345d.lib
	opencv_face345d.lib
	opencv_features2d345d.lib
	opencv_flann345d.lib
	opencv_fuzzy345d.lib
	opencv_hfs345d.lib
	opencv_highgui345d.lib
	opencv_img_hash345d.lib
	opencv_imgcodecs345d.lib
	opencv_imgproc345d.lib
	opencv_line_descriptor345d.lib
	opencv_ml345d.lib
	opencv_objdetect345d.lib
	opencv_optflow345d.lib
	opencv_phase_unwrapping345d.lib
	opencv_photo345d.lib
	opencv_plot345d.lib
	opencv_reg345d.lib
	opencv_rgbd345d.lib
	opencv_saliency345d.lib
	opencv_shape345d.lib
	opencv_stereo345d.lib
	opencv_stitching345d.lib
	opencv_structured_light345d.lib
	opencv_superres345d.lib
	opencv_surface_matching345d.lib
	opencv_text345d.lib
	opencv_tracking345d.lib
	opencv_ts345d.lib
	opencv_video345d.lib
	opencv_videoio345d.lib
	opencv_videostab345d.lib
	opencv_xfeatures2d345d.lib
	opencv_ximgproc345d.lib
	opencv_xobjdetect345d.lib
	opencv_xphoto345d.lib)
	
set (OPENCV_INCLUDE 
	${OPENCV_FOLDER}/build
	${OPENCV_FOLDER}/include
	${OPENCV_FOLDER}/include/opencv
	${OPENCV_FOLDER}/modules/core/include
	${OPENCV_FOLDER}/modules/flann/include
	${OPENCV_FOLDER}/modules/imgproc/include
	${OPENCV_FOLDER}/modules/ml/include
	${OPENCV_EXTRA_MODULE_FOLDER}/phase_unwrapping/include
	${OPENCV_FOLDER}/modules/photo/include
	${OPENCV_EXTRA_MODULE_FOLDER}/plot/include
	${OPENCV_EXTRA_MODULE_FOLDER}/reg/include
	${OPENCV_EXTRA_MODULE_FOLDER}/surface_matching/include
	${OPENCV_FOLDER}/modules/video/include
	${OPENCV_EXTRA_MODULE_FOLDER}/xphoto/include
	${OPENCV_FOLDER}/modules/dnn/include
	${OPENCV_EXTRA_MODULE_FOLDER}/fuzzy/include
	${OPENCV_EXTRA_MODULE_FOLDER}/hfs/include
	${OPENCV_EXTRA_MODULE_FOLDER}/img_hash/include
	${OPENCV_FOLDER}/modules/imgcodecs/include
	${OPENCV_FOLDER}/modules/shape/include
	${OPENCV_FOLDER}/modules/videoio/include
	${OPENCV_FOLDER}/modules/highgui/include
	${OPENCV_FOLDER}/modules/superres/include
	${OPENCV_FOLDER}/modules/ts/include
	${OPENCV_EXTRA_MODULE_FOLDER}/bioinspired/include
	${OPENCV_EXTRA_MODULE_FOLDER}/dnn_objdetect/include
	${OPENCV_FOLDER}/modules/features2d/include
	${OPENCV_EXTRA_MODULE_FOLDER}/line_descriptor/include
	${OPENCV_EXTRA_MODULE_FOLDER}/saliency/include
	${OPENCV_EXTRA_MODULE_FOLDER}/text/include
	${OPENCV_FOLDER}/modules/calib3d/include
	${OPENCV_EXTRA_MODULE_FOLDER}/ccalib/include
	${OPENCV_EXTRA_MODULE_FOLDER}/datasets/include
	${OPENCV_FOLDER}/modules/objdetect/include
	${OPENCV_EXTRA_MODULE_FOLDER}/rgbd/include
	${OPENCV_EXTRA_MODULE_FOLDER}/stereo/include
	${OPENCV_EXTRA_MODULE_FOLDER}/structured_light/include
	${OPENCV_EXTRA_MODULE_FOLDER}/tracking/include
	${OPENCV_FOLDER}/modules/videostab/include
	${OPENCV_EXTRA_MODULE_FOLDER}/xfeatures2d/include
	${OPENCV_EXTRA_MODULE_FOLDER}/ximgproc/include
	${OPENCV_EXTRA_MODULE_FOLDER}/xobjdetect/include
	${OPENCV_EXTRA_MODULE_FOLDER}/aruco/include
	${OPENCV_EXTRA_MODULE_FOLDER}/bgsegm/include
	${OPENCV_EXTRA_MODULE_FOLDER}/dpm/include
	${OPENCV_EXTRA_MODULE_FOLDER}/face/include
	${OPENCV_EXTRA_MODULE_FOLDER}/optflow/include
	${OPENCV_FOLDER}/modules/stitching/include)
	
project (CVBridgePlugins)


add_subdirectory(Plugin)

add_subdirectory(AVMDemo)

add_subdirectory(Calibration)