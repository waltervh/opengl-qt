pipeline {
  agent {
    docker {
      image 'python:3.5.1'
    }

  }
  stages {
    stage('build') {
      parallel {
        stage('build') {
          steps {
            sh 'python --version'
          }
        }
        stage('mytest') {
          steps {
            sh 'echo \'Executing a shell script\''
          }
        }
      }
    }
  }
}