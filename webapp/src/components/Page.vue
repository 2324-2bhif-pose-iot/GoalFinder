<script setup lang="ts">
  import Card from "@/components/Card.vue";

  const props = defineProps([
    'title',
  ]);
</script>

<template>
  <div id="page">
    <h1 id="page-title">{{ title }}</h1>
    <Card class="page-content" glow="true">
      <slot/>
    </Card>
  </div>
</template>

<style scoped>
  #page-title {
    color: cornflowerblue;
  }

  #page {
    padding-right: 15px;
    padding-left: 15px;
    margin-right: auto;
    margin-left: auto;
  }
  @media (min-width: 768px) {
    #page {
      width: 750px;
    }
  }
  @media (min-width: 992px) {
    #page {
      width: 970px;
    }
  }
  @media (min-width: 1200px) {
    #page {
      width: 1170px;
    }
  }

  .page-content {
    margin-top: 5vh;
  }

  @media (min-width: 768px) {
    .page-content {
      margin-top: 0;
    }
  }
</style>