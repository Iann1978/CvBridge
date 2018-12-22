cmake_minimum_required (VERSION 2.6)

set(OPENCV_FOLDER E:/githome/opencv/opencv3)
set(OPENCV_EXTRA_MODULE_FOLDER E:/githome/opencv/opencv_contrib3/modules)

set(OPENCV_LIB opencv_aruco344d.lib
	opencv_bgsegm344d.lib
	opencv_bioinspired344d.lib
	opencv_calib3d344d.lib
	opencv_ccalib344d.lib
	opencv_core344d.lib
	opencv_datasets344d.lib
	opencv_dnn_objdetect344d.lib
	opencv_dnn344d.lib
	opencv_dpm344d.lib
	opencv_face344d.lib
	opencv_features2d344d.lib
	opencv_flann344d.lib
	opencv_fuzzy344d.lib
	opencv_hfs344d.lib
	opencv_highgui344d.lib
	opencv_img_hash344d.lib
	opencv_imgcodecs344d.lib
	opencv_imgproc344d.lib
	opencv_line_descriptor344d.lib
	opencv_ml344d.lib
	opencv_objdetect344d.lib
	opencv_optflow344d.lib
	opencv_phase_unwrapping344d.lib
	opencv_photo344d.lib
	opencv_plot344d.lib
	opencv_reg344d.lib
	opencv_rgbd344d.lib
	opencv_saliency344d.lib
	opencv_shape344d.lib
	opencv_stereo344d.lib
	opencv_stitching344d.lib
	opencv_structured_light344d.lib
	opencv_superres344d.lib
	opencv_surface_matching344d.lib
	opencv_text344d.lib
	opencv_tracking344d.lib
	opencv_ts344d.lib
	opencv_video344d.lib
	opencv_videoio344d.lib
	opencv_videostab344d.lib
	opencv_xfeatures2d344d.lib
	opencv_ximgproc344d.lib
	opencv_xobjdetect344d.lib
	opencv_xphoto344d.lib)
	
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