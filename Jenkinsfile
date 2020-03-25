#!/usr/bin/env groovy

node('delphyne-linux-bionic-unprovisioned') {
  // From empirical evidence it takes ~10 minutes to install dependencies
  // and ~20 minutes to build and run the tests.  That adds up to 30 minutes
  // which we double to 60 to give us enough leeway.
  timeout(60) {
    ansiColor('xterm') {
      try {
        stage('checkout') {
          dir('src/maliput_dragway') {
            checkout scm
          }
        }
        stage('checkout_index') {
          sh 'src/maliput_dragway/ci/jenkins/checkout_index'
        }
        withEnv(['COLCON_BUILD_EXTRA_ARGS=--packages-up-to maliput_dragway',
                 'COLCON_TEST_EXTRA_ARGS=--packages-up-to maliput_dragway']) {
          load './index/ci/jenkins/pipeline.groovy'
        }
      } finally {
        cleanWs(notFailBuild: true)
      }
    }
  }
}