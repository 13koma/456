import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/workspaces/grasp_jaka_ws/install/jaka_tf_tools'
