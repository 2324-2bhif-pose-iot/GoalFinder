<script setup>
  import {ref} from "vue";

  const username = ref("");
  const password = ref("");

  function printUsrAndPwd() {
    console.log("Username: " + username.value);
    console.log("Password: " + password.value);
  }
</script>

<template>
  <div class="container-fluid" id="login-form">
    <div class="card">
      <div class="card-header">Login</div>
      <div class="card-body">
        <div class="mb-3">
          <label class="form-label">Username</label>
          <input class="form-control" type="text" placeholder="Username" v-model="username">
        </div>
        <div class="mb-3">
          <label class="form-label">Password</label>
          <input class="form-control" type="password" placeholder="Password" v-model="password">
        </div>
        <button @click="printUsrAndPwd" class="btn btn-primary">Login</button>
      </div>
    </div>
  </div>
</template>

<style scoped>
  #login-form {
    width: 30rem;
    min-height: 100%;
  }
</style>