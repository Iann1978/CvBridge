cmake_minimum_required (VERSION 2.6)

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
	
project (CVBridgePlugins)


add_subdirectory(Plugin)

add_subdirectory(AVMDemo)

add_subdirectory(Calibration)