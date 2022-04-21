<template>
  <div class="card mx-3 my-3 skeleton-card" style="max-width: 540px">
    <div class="row g-0">
      <div class="col-md-4 skeleton-img">
        <ImageSkeleton />
      </div>
      <div class="col-md-8">
        <div class="card-body">
          <h5 class="card-title skeleton"></h5>
          <p class="card-text skeleton"></p>
          <p class="card-text skeleton"></p>
          <p class="card-text skeleton"></p>
          <p class="card-text skeleton"></p>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import ImageSkeleton from "../components/ImageSkeleton.vue";
export default {
  name: "CardSkeleton",
  components: { ImageSkeleton },
};
</script>

<style scoped>
.card-title {
  width: 100%;
  height: 1.25rem;
  border-radius: 0.125rem;
}

.card-text {
  width: 100%;
  height: 0.75rem;
  border-radius: 0.125rem;
}

.card-text:nth-child(4) {
  width: 80%;
}

.card-text:last-child {
  height: 0.5rem;
}

@media (max-width: 767px) {
  .skeleton-img {
    height: 15rem;
  }
}
</style>
